#include "Image.h"
#include "EscapeTheCave.h"
#include "ChadBuff.h"
#include "Player.h"
#include "GameLevel.h"
#include "Bomb.h"

Image * ChadBuff::image = nullptr;

ChadBuff::ChadBuff(): hasToBeDestroyed(false) {
    if(image == nullptr) {
        image = new Image("Resources/Buffs/ChadBuff.png");
    }

    sprite = new Sprite(image);
    float xCoord = (float) image->Width()/2;
    float yCoord = (float) image->Height()/2;

    BBox(new Rect(-xCoord, -yCoord, xCoord, yCoord));
    type = DROPPABLE_ITEM;
}

ChadBuff::~ChadBuff() {
    delete sprite;
}

void ChadBuff::OnCollision(Object * obj) {
    if(hasToBeDestroyed) return;

    if(obj->Type() == PLAYER) {
        Player * player = (Player *) obj;
        player->ActivateGentleBotMode();
        hasToBeDestroyed = true;

        return;
    }
}

void ChadBuff::Update() {
    if(hasToBeDestroyed) GameLevel::GetScene()->Delete();
}

void ChadBuff::Draw() {
    sprite->Draw(x, y, Layer::MIDDLE);
}
