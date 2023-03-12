#include "EscapeTheCave.h"
#include "Player.h"
#include "Stone.h"

Player::Player() {
    spriteUp = new Sprite("Resources/PlayerUp.png");
    spriteDown = new Sprite("Resources/PlayerDown.png");
    spriteLeft = new Sprite("Resources/PlayerLeft.png");
    spriteRight = new Sprite("Resources/PlayerRight.png");
    
    BBox(new Rect(-56, -56, 56, 56));
    MoveTo(window->CenterX() + 1, window->CenterY());

    type = PLAYER;
    state = UP;
    spriteSize = spriteUp->Width();
}

Player::~Player() {
    delete spriteUp;
    delete spriteDown;
    delete spriteLeft;
    delete spriteRight;
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
            int directionModifier = 
                collisionValue * (state == UP ? 1 : -1);

            MoveTo(x, stone->Y() + directionModifier);
            break;
        }

        case LEFT:
        case RIGHT: {
            int directionModifier = 
                collisionValue * (state == LEFT ? 1 : -1);

            MoveTo(stone->X() + directionModifier, y);
            break;
        }
    }
}

PLAYERSTATE Player::GetStateBasedOnWindowKey() {
    if(window->KeyDown(VK_LEFT)) return LEFT;
    if(window->KeyDown(VK_RIGHT)) return RIGHT;
    if(window->KeyDown(VK_UP)) return UP;
    if(window->KeyDown(VK_DOWN)) return DOWN;
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
    if(energy > 0) energy -= 0.05;
}

void Player::Draw() {
    switch(state) {
        case UP: spriteUp->Draw(x, y, Layer::UPPER); break;
        case DOWN: spriteDown->Draw(x, y, Layer::UPPER); break;
        case LEFT: spriteLeft->Draw(x, y, Layer::UPPER); break;
        case RIGHT: spriteRight->Draw(x, y, Layer::UPPER);
    }
}
