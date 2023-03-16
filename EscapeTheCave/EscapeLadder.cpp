#include "EscapeLadder.h"
#include "Player.h"
#include "Game.h"
#include "EscapeTheCave.h"

EscapeLadder::EscapeLadder(): playerHasEscaped(false) {
    sprite = new Sprite("Resources/Ladder.png");

    float boxCoord = (float) sprite->Width()/2;
    BBox(new Rect(-boxCoord, -boxCoord, boxCoord, boxCoord));

    type = ESCAPE_LADDER;
    timer = new Timer();
}

EscapeLadder::~EscapeLadder() {
    delete sprite;
}

void EscapeLadder::OnCollision(Object * obj) {
    if(obj->Type() != PLAYER) return;

    if(timer->NotStarted()) {
        timer->Start();
        return;
    }
    if(timer->Elapsed() <= 1.0f) return;

    Player * player = (Player *) obj;
    player->PlayerHasEscaped(true);
}

void EscapeLadder::Update() {
}

void EscapeLadder::Draw() {
    sprite->Draw(x, y, Layer::UPPER);
}
