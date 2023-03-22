#include "Image.h"
#include "EscapeTheCave.h"
#include "MiningBuff.h"
#include "Player.h"
#include "GameLevel.h"
#include "Bomb.h"

Image * MiningBuff::image = nullptr;

MiningBuff::MiningBuff(): hasToBeDestroyed(false) {
    if(image == nullptr) {
        image = new Image("Resources/Buffs/MiningBuff.png");
    }

    sprite = new Sprite(image);
    float boxCoord = (float) image->Width()/2;
    BBox(new Rect(-boxCoord, -boxCoord, boxCoord, boxCoord));
    type = DROPPABLE_ITEM;
}

MiningBuff::~MiningBuff() {
    delete sprite;
}

void MiningBuff::OnCollision(Object * obj) {
    if(hasToBeDestroyed) return;
    uint objType = obj->Type();

    if(objType == PLAYER) {
        Player * player = (Player *) obj;
        player->BuffMiningSpeed();
        hasToBeDestroyed = true;

        return;
    }

    if(objType == BOMB) {
        Bomb * bomb = (Bomb *) obj;
        if(bomb->BombType() == GENERATED) hasToBeDestroyed = true;

        return;
    }
}

void MiningBuff::Update() {
    if(hasToBeDestroyed) GameLevel::GetScene()->Delete();
}

void MiningBuff::Draw() {
    sprite->Draw(x, y, Layer::MIDDLE);
}
