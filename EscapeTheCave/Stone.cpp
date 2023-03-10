#include "Stone.h"
#include "EscapeTheCave.h"

Stone::Stone(Image * stoneImage) {
    sprite = new Sprite(stoneImage);
    
    BBox(new Rect(-32, -32, 32, 32));
    type = STONE;
}

Stone::~Stone() {
    delete sprite;
}

void Stone::OnCollision(Object * obj) {
}

void Stone::Update() {
}

void Stone::Draw() {
    sprite->Draw(x, y, Layer::UPPER);
}
