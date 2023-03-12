#include "Bomb.h"
#include "EscapeTheCave.h"
#include "Player.h"
#include "Stone.h"
#include "Image.h"

Image * Bomb::explosionImage = nullptr;

Bomb::Bomb(BOMBTYPE bombType, Image * image): bombType(bombType), hasExploded(false) {
    if(explosionImage == nullptr) {
        explosionImage = new Image("Resources/Bomb/Explosion.png");
    }

    timer = new Timer();
    sprite = new Sprite(image);
    BBox(new Rect(-32, -32, 32, 32));

    type = BOMB;
    timer->Start();
}

Bomb::~Bomb() {
    delete sprite;
    delete timer;
}

void Bomb::OnCollision(Object * obj) {
    if(obj->Type() == STONE) StoneCollision(obj);
    else if(obj->Type() == PLAYER) PlayerCollision(obj);
}

void Bomb::StoneCollision(Object * obj) {
    Stone * stone = (Stone *) obj;
    stone->Destroy();
}

void Bomb::PlayerCollision(Object * obj) {
    Player * player = (Player *) obj;
}

void Bomb::Update() {
    if(hasExploded && timer->Elapsed() >= 0.2) {
        Game::GetScene()->Delete(this, MOVING);
        return;
    }

    if(timer->Elapsed() >= 3.0f) {
        sprite = new Sprite(explosionImage);
        BBox(new Circle(90.0f));

        hasExploded = true;
        timer->Reset();
    }
}

void Bomb::Draw() {
    sprite->Draw(x, y, Layer::UPPER);
}
