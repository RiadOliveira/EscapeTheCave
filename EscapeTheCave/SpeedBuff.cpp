#include "Image.h"
#include "EscapeTheCave.h"
#include "SpeedBuff.h"
#include "Player.h"
#include "GameLevel.h"

Image * SpeedBuff::image = nullptr;

SpeedBuff::SpeedBuff(): hasToBeDestroyed(false) {
    if(image == nullptr) {
        image = new Image("Resources/Buffs/SpeedBuff.png");
    }

    sprite = new Sprite(image);
    float boxCoord = image->Width()/2;
    BBox(new Rect(-boxCoord, -boxCoord, boxCoord, boxCoord));
    type = DROPPABLE_ITEM;
}

SpeedBuff::~SpeedBuff() {
    delete sprite;
}

void SpeedBuff::OnCollision(Object * obj) {
    if(hasToBeDestroyed) return;
    bool isPlayer = obj->Type() == PLAYER;
    bool isBomb = obj->Type() == BOMB;

    if(isPlayer) {
        Player * player = (Player *) obj;
        player->BuffBatteryTime();
    }
    if(isPlayer || isBomb) hasToBeDestroyed = true;
}

void SpeedBuff::Update() {
    if(hasToBeDestroyed) GameLevel::GetScene()->Delete();
}

void SpeedBuff::Draw() {
    sprite->Draw(x, y, Layer::MIDDLE);
}
