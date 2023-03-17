#include "Image.h"
#include "EscapeTheCave.h"
#include "BatteryBuff.h"
#include "Player.h"
#include "GameLevel.h"

Image * BatteryBuff::image = nullptr;

BatteryBuff::BatteryBuff(): hasToBeDestroyed(false) {
    if(image == nullptr) {
        image = new Image("Resources/Buffs/BatteryBuff.png");
    }

    sprite = new Sprite(image);
    float boxCoord = image->Width()/2;
    BBox(new Rect(-boxCoord, -boxCoord, boxCoord, boxCoord));
    type = DROPPABLE_ITEM;
}

BatteryBuff::~BatteryBuff() {
    delete sprite;
}

void BatteryBuff::OnCollision(Object * obj) {
    if(hasToBeDestroyed) return;
    bool isPlayer = obj->Type() == PLAYER;
    bool isBomb = obj->Type() == BOMB;

    if(isPlayer) {
        Player * player = (Player *) obj;
        player->BuffBatteryTime();
    }
    if(isPlayer || isBomb) hasToBeDestroyed = true;
}

void BatteryBuff::Update() {
    if(hasToBeDestroyed) GameLevel::GetScene()->Delete();
}

void BatteryBuff::Draw() {
    sprite->Draw(x, y, Layer::MIDDLE);
}
