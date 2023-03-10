#include "EscapeTheCave.h"
#include "Player.h"
#include "Pivot.h"

Player::Player() {
    sprite = new Sprite("Resources/Miner.png");
    
    BBox(new Rect(-32, -32, 32, 32));
    MoveTo(window->CenterX(), window->CenterY());
    type = PLAYER;
}

Player::~Player() {
    delete sprite;
}

void Player::OnCollision(Object * obj) {
    if (obj->Type() == PIVOT) PivotCollision(obj);
}

void Player::PivotCollision(Object * obj) {
    Pivot * p = (Pivot*)obj;
}

void Player::Update() {
    if(window->KeyDown(VK_LEFT)) {
        Translate(-speed * gameTime, 0);
    }

    if(window->KeyDown(VK_RIGHT)) {
        Translate(speed * gameTime, 0);
    }

    if(window->KeyDown(VK_UP)) {
        Translate(0, -speed * gameTime);
    }

    if(window->KeyDown(VK_DOWN)) {
        Translate(0, speed*gameTime);
    }

    if (x+20 < 0)
        MoveTo(window->Width()+20.f, Y());

    if (x-20 > window->Width())
        MoveTo(-20.0f, Y());

    if (Y()+20 < 0)
        MoveTo(x, window->Height()+20.0f);

    if (Y()-20 > window->Height())
        MoveTo(x, -20.0f);
}

void Player::Draw() {
    sprite->Draw(x, y, Layer::UPPER);
}
