#include "Image.h"
#include "EscapeTheCave.h"
#include "BatteryBuff.h"
#include "Player.h"
#include "GameLevel.h"
#include "Bomb.h"

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
    uint objType = obj->Type();

    if(objType == PLAYER) {
        Player * player = (Player *) obj;
        player->BuffBatteryTime();
        hasToBeDestroyed = true;

        return;
    }

    if(objType == BOMB) {
        Bomb * bomb = (Bomb *) obj;
        if(bomb->BombType() == GENERATED) hasToBeDestroyed = true;

        return;
    }
}

void BatteryBuff::Update() {
    if(hasToBeDestroyed) GameLevel::GetScene()->Delete();
}

void BatteryBuff::Draw() {
    sprite->Draw(x, y, Layer::MIDDLE);
}
