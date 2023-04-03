#include "EscapeTheCave.h"
#include "Player.h"
#include "Stone.h"
#include "Bomb.h"
#include "GameLevel.h"
#include "MiningPoint.h"

void Player::SetPlayerSprites() {
    if(sprites != nullptr) return;

    string spritesPath = "Resources/Player";
    sprites = new Sprite*[4];

    sprites[UP] = new Sprite(spritesPath + "/PlayerUp.png");
    sprites[DOWN] = new Sprite(spritesPath + "/PlayerDown.png");
    sprites[LEFT] = new Sprite(spritesPath + "/PlayerLeft.png");
    sprites[RIGHT] = new Sprite(spritesPath + "/PlayerRight.png");

    spriteSize = (float) sprites[UP]->Width();
}

Player::Player():
    state(RIGHT), battery(new Battery()), radar(new Radar()),
    bombsQuantity(1), playerHasEscaped(false), gentleBotMode(false),
    speed(120.0f), miningSpeed(0.5f)
{
    SetPlayerSprites();

    float boxCoord = spriteSize/2;
    BBox(new Rect(-boxCoord, -boxCoord, boxCoord, boxCoord));
    MoveTo(window->CenterX() + 1, window->CenterY());
    type = PLAYER;
}

Player::~Player() {
    for(int ind=0 ; ind<4 ; ind++) {
        delete sprites[ind];
        if(gentleBotMode) delete gentleBotSprites[ind];
    }
    delete[] sprites;
    if(gentleBotMode) delete[] gentleBotSprites;

    delete battery;
    delete radar;
}

void Player::ResetDataToNewLevel(int levelBombsQuantity) {
    state = RIGHT;
    playerHasEscaped = false;
    battery->ResetDataToNewLevel();
    radar->ResetDataToNewLevel();
    bombsQuantity = levelBombsQuantity;
    gentleBotMode = false;

    MoveTo(window->CenterX() + 1, window->CenterY());
}

void Player::ActivateGentleBotMode() {
    gentleBotSprites = new Sprite*[4];
    string spritesPath = "Resources/Player";

    gentleBotSprites[UP] = new Sprite(spritesPath + "/GentleBotUp.png");
    gentleBotSprites[DOWN] = new Sprite(spritesPath + "/GentleBotDown.png");
    gentleBotSprites[LEFT] = new Sprite(spritesPath + "/GentleBotLeft.png");
    gentleBotSprites[RIGHT] = new Sprite(spritesPath + "/GentleBotRight.png");

    battery->RechargeBattery();
    gentleBotMode = true;
}

void Player::AddToScene() {
    Scene * &scene = GameLevel::GetScene();

    scene->Add(this, MOVING);
    scene->Add(battery, STATIC);
    scene->Add(radar, STATIC);
    scene->Add(new MiningPoint(), MOVING);
}

void Player::RemoveFromScene() {
    Scene * &scene = GameLevel::GetScene();

    scene->Remove(this, MOVING);
    scene->Remove(battery, STATIC);
    scene->Remove(radar, STATIC);
    if(!gentleBotMode) return;

    for(int ind=0 ; ind<4 ; ind++) {
        delete gentleBotSprites[ind];
    }
    delete[] gentleBotSprites;
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

    if(window->KeyPress('X')) radar->ActivateRadar();
}

void Player::Draw() {
    if(state == NONE) return;
    Sprite * selectedSprite = 
        gentleBotMode ? gentleBotSprites[state] : sprites[state];

    selectedSprite->Draw(x, y, Layer::UPPER);
}
