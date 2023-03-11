#include "EscapeTheCave.h"
#include "Player.h"
#include "Pivot.h"
#include <string>

Player::Player() {
    spriteUp = new Sprite("Resources/playerUp.jpg");
    spriteDown = new Sprite("Resources/playerDown.jpg");
    spriteLeft = new Sprite("Resources/playerLeft.jpg");
    spriteRight = new Sprite("Resources/playerRight.jpg");
    
    BBox(new Rect(-32, -32, 32, 32));
    MoveTo(window->CenterX(), window->CenterY());

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
    if (obj->Type() == PIVOT) PivotCollision(obj);
}

void Player::PivotCollision(Object * obj) {
    Pivot * p = (Pivot*)obj;
}

PLAYERSTATE Player::GetStateBasedOnWindowKey() {
    if(window->KeyDown(VK_LEFT)) return LEFT;
    if(window->KeyDown(VK_RIGHT)) return RIGHT;
    if(window->KeyDown(VK_UP)) return UP;
    if(window->KeyDown(VK_DOWN)) return DOWN;
    return NONE;
}

void Player::VerifyAndMovePlayerIfExceededWindow() {
    int halfSpriteSize = spriteSize/2;

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
    switch(updatedState) {
        case LEFT: {
            if(state != LEFT) state = LEFT;
            else Translate(-speed * gameTime, 0);
            break;
        }
        case RIGHT: {
            if(state != RIGHT) state = RIGHT;
            else Translate(speed * gameTime, 0);
            break;
        }
        case UP: {
            if(state != UP) state = UP;
            else Translate(0, -speed * gameTime);
            break;
        }
        case DOWN: {
            if(state != DOWN) state = DOWN;
            else Translate(0, speed*gameTime);
            break;
        }
    }

    VerifyAndMovePlayerIfExceededWindow();
}

void Player::Update() {
    HandleMovePlayer(GetStateBasedOnWindowKey());
}

void Player::Draw() {
    switch(state) {
        case UP: spriteUp->Draw(x, y, Layer::UPPER); break;
        case DOWN: spriteDown->Draw(x, y, Layer::UPPER); break;
        case LEFT: spriteLeft->Draw(x, y, Layer::UPPER); break;
        case RIGHT: spriteRight->Draw(x, y, Layer::UPPER);
    }
}
