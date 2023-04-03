#include "EscapePoint.h"
#include "Player.h"
#include "Game.h"
#include "EscapeTheCave.h"

EscapePoint::EscapePoint(bool finalEscape) {
    sprite = new Sprite(
        finalEscape ? "Resources/Escape.png" : "Resources/Generator.png"
    );

    float boxCoord = ((float)sprite->Width() / 2) - 5;
    BBox(new Rect(-boxCoord, -boxCoord, boxCoord, boxCoord));

    type = ESCAPE_POINT;
    timer = new Timer();
}

EscapePoint::~EscapePoint() {
    delete sprite;
}

void EscapePoint::OnCollision(Object * obj) {
    if(obj->Type() != PLAYER) return;

    if(timer->NotStarted()) {
        timer->Start();
        return;
    }
    if(timer->Elapsed() <= 0.5f) return;

    Player * player = (Player *) obj;
    player->PlayerHasEscaped(true);
}

void EscapePoint::Update() {
}

void EscapePoint::Draw() {
    sprite->Draw(x, y, Layer::UPPER);
}
