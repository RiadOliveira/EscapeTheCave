#include "Generator.h"
#include "Player.h"
#include "Game.h"
#include "EscapeTheCave.h"

Generator::Generator(): playerHasEscaped(false) {
    sprite = new Sprite("Resources/Generator.png");

    float boxCoord = (float) sprite->Width()/2;
    BBox(new Rect(-boxCoord, -boxCoord, boxCoord, boxCoord));

    type = GENERATOR;
    timer = new Timer();
}

Generator::~Generator() {
    delete sprite;
}

void Generator::OnCollision(Object * obj) {
    if(obj->Type() != PLAYER) return;

    if(timer->NotStarted()) {
        timer->Start();
        return;
    }
    if(timer->Elapsed() <= 0.5f) return;

    Player * player = (Player *) obj;
    player->PlayerHasEscaped(true);
}

void Generator::Update() {
}

void Generator::Draw() {
    sprite->Draw(x, y, Layer::UPPER);
}
