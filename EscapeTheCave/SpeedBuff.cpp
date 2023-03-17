#include "Image.h"
#include "EscapeTheCave.h"
#include "SpeedBuff.h"
#include "Player.h"
#include "GameLevel.h"
#include "Bomb.h"

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
    uint objType = obj->Type();

    if(objType == PLAYER) {
        Player * player = (Player *) obj;
        player->BuffSpeed();
        hasToBeDestroyed = true;

        return;
    }

    if(objType == BOMB) {
        Bomb * bomb = (Bomb *) obj;
        if(bomb->BombType() == GENERATED) hasToBeDestroyed = true;

        return;
    }
}

void SpeedBuff::Update() {
    if(hasToBeDestroyed) GameLevel::GetScene()->Delete();
}

void SpeedBuff::Draw() {
    sprite->Draw(x, y, Layer::MIDDLE);
}
