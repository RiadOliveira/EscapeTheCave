#include "Image.h"
#include "EscapeTheCave.h"
#include "MiningBuff.h"
#include "Player.h"
#include "GameLevel.h"

Image * MiningBuff::image = nullptr;

MiningBuff::MiningBuff(): hasToBeDestroyed(false) {
    if(image == nullptr) {
        image = new Image("Resources/Buffs/MiningBuff.png");
    }

    sprite = new Sprite(image);
    float boxCoord = image->Width()/2;
    BBox(new Rect(-boxCoord, -boxCoord, boxCoord, boxCoord));
    type = DROPPABLE_ITEM;
}

MiningBuff::~MiningBuff() {
    delete sprite;
}

void MiningBuff::OnCollision(Object * obj) {
    if(hasToBeDestroyed) return;
    bool isPlayer = obj->Type() == PLAYER;
    bool isBomb = obj->Type() == BOMB;

    if(isPlayer) {
        Player * player = (Player *) obj;
        player->BuffBatteryTime();
    }
    if(isPlayer || isBomb) hasToBeDestroyed = true;
}

void MiningBuff::Update() {
    if(hasToBeDestroyed) GameLevel::GetScene()->Delete();
}

void MiningBuff::Draw() {
    sprite->Draw(x, y, Layer::MIDDLE);
}
