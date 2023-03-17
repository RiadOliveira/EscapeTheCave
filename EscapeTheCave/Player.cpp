#include "EscapeTheCave.h"
#include "Player.h"
#include "Stone.h"
#include "Bomb.h"
#include "GameLevel.h"

Player::Player(Battery * battery):
    state(RIGHT), bombsQuantity(1), battery(battery),
    playerHasEscaped(false), speed(120.0f), miningSpeed(0.5f)
{
    spriteUp = new Sprite("Resources/Player/PlayerUp.png");
    spriteDown = new Sprite("Resources/Player/PlayerDown.png");
    spriteLeft = new Sprite("Resources/Player/PlayerLeft.png");
    spriteRight = new Sprite("Resources/Player/PlayerRight.png");
    
    spriteSize = (float) spriteUp->Width();
    float boxCoord = spriteSize/2;

    BBox(new Rect(-boxCoord, -boxCoord, boxCoord, boxCoord));
    MoveTo(window->CenterX() + 1, window->CenterY());
    type = PLAYER;
}

void Player::ResetDataToNewLevel(int levelBombsQuantity) {
    state = RIGHT;
    playerHasEscaped = false;
    battery->ResetDataToNewLevel();
    bombsQuantity = levelBombsQuantity;

    MoveTo(window->CenterX() + 1, window->CenterY());
}

Player::~Player() {
    delete spriteUp;
    delete spriteDown;
    delete spriteLeft;
    delete spriteRight;
    delete battery;
}

void Player::OnCollision(Object * obj) {
    if (obj->Type() == STONE) StoneCollision(obj);
}

void Player::StoneCollision(Object * obj) {
    Stone * stone = (Stone*) obj;

    float collisionValue = spriteSize/2 + stone->SpriteSize()/2;
    bool hasExceededStone = 
        abs(x - stone->X()) < collisionValue &&
        abs(y - stone->Y()) < collisionValue;

    if(!hasExceededStone) return;
    switch(state) {
        case UP:
        case DOWN: {
            float directionModifier = 
                collisionValue * (state == UP ? 1 : -1);

            MoveTo(x, stone->Y() + directionModifier);
            break;
        }

        case LEFT:
        case RIGHT: {
            float directionModifier = 
                collisionValue * (state == LEFT ? 1 : -1);

            MoveTo(stone->X() + directionModifier, y);
            break;
        }
    }
}

PLAYERSTATE Player::GetStateBasedOnWindowKey() {
    if(window->KeyDown(VK_LEFT) || window->KeyDown('A')) return LEFT;
    if(window->KeyDown(VK_RIGHT)|| window->KeyDown('D')) return RIGHT;
    if(window->KeyDown(VK_UP) || window->KeyDown('W')) return UP;
    if(window->KeyDown(VK_DOWN) || window->KeyDown('S')) return DOWN;
    return NONE;
}

void Player::VerifyAndMovePlayerIfExceededWindow() {
    float halfSpriteSize = spriteSize/2;

    int windowWidth = window->Width();
    if (x - halfSpriteSize < 0) {
        MoveTo(halfSpriteSize, y);
        return;
    }

    if (x + halfSpriteSize > windowWidth) {
        MoveTo(windowWidth - halfSpriteSize, y);
        return;
    }

    int windowHeight = window->Height();
    if (y - halfSpriteSize < 0) {
        MoveTo(x, halfSpriteSize);
        return;
    }

    if (y + halfSpriteSize > windowHeight) {
        MoveTo(x, windowHeight - halfSpriteSize);
        return;
    }
}

void Player::HandleMovePlayer(PLAYERSTATE updatedState) {
    if(updatedState == NONE) return;

    if(updatedState == LEFT) {
        if(state != LEFT) state = LEFT;
        else Translate(-speed * gameTime, 0);
    }

    if(updatedState == RIGHT) {
        if(state != RIGHT) state = RIGHT;
        else Translate(speed * gameTime, 0);
    }

    if(updatedState == UP) {
        if(state != UP) state = UP;
        else Translate(0, -speed * gameTime);
    }

    if(updatedState == DOWN) {
        if(state != DOWN) state = DOWN;
        else Translate(0, speed*gameTime);
    }

    VerifyAndMovePlayerIfExceededWindow();
}

void Player::Update() {
    HandleMovePlayer(GetStateBasedOnWindowKey());

    if(window->KeyPress('Z') && bombsQuantity-- > 0) {
        Bomb * playerBomb = new Bomb(PLAYED);
        playerBomb->MoveTo(x, y);
        GameLevel::GetScene()->Add(playerBomb, MOVING);
    }
}

void Player::Draw() {
    switch(state) {
        case UP: spriteUp->Draw(x, y, Layer::UPPER); break;
        case DOWN: spriteDown->Draw(x, y, Layer::UPPER); break;
        case LEFT: spriteLeft->Draw(x, y, Layer::UPPER); break;
        case RIGHT: spriteRight->Draw(x, y, Layer::UPPER);
    }
}
