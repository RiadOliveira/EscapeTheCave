#include "Generator.h"
#include "Player.h"
#include "Game.h"
#include "EscapeTheCave.h"

Generator::Generator(int level): playerHasEscaped(false) {
    Image* generator = new Image("Resources/Generator.png");
    Image* escape = new Image("Resources/Escape.png");

    if (level > 10) {
        sprite = new Sprite(generator);
    }
    else {
        sprite = new Sprite(escape);
    }

    float boxCoord = (float) sprite->Width()/2;
    BBox(new Rect((-boxCoord - 5), (-boxCoord - 5), (boxCoord - 5), (boxCoord - 5)));

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
