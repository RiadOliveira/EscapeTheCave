#include "Stone.h"
#include "Player.h"
#include "GameLevel.h"
#include "Pivot.h"
#include "EscapeTheCave.h"

Image ** Stone::stoneImages = nullptr;

Stone::Stone(uint maxDurability):
    maxDurability(maxDurability), durability(maxDurability)
{
    if(stoneImages == nullptr) {
        Image * completeStoneImg = new Image("Resources/Stone/CompleteStone.png");
        Image * brokenStoneImg = new Image("Resources/Stone/BrokenStone.png");

        stoneImages = new Image*[2]{brokenStoneImg, completeStoneImg};
    }

    spritesQuantity = maxDurability > 1 ? 2 : 1;
    sprites = new Sprite*[spritesQuantity];
    for(uint ind=0 ; ind<spritesQuantity ; ind++) {
        sprites[ind] = new Sprite(stoneImages[ind]);
    }

    spriteSize = (float) stoneImages[0]->Width();
    float boxCoord = spriteSize/2;

    BBox(new Rect(-boxCoord, -boxCoord, boxCoord, boxCoord));
    type = STONE;
}

Stone::Stone(uint maxDurability, Object * dropingItem):
    Stone(maxDurability)
{
    this->dropingItem = dropingItem;
}

Stone::~Stone() {
    if(dropingItem) {
        dropingItem->MoveTo(x, y);
        GameLevel::GetScene()->Add(dropingItem, STATIC);
    }

    Pivot * pivot = new Pivot();
    pivot->MoveTo(x, y);
    GameLevel::GetScene()->Add(pivot, STATIC);

    for(uint ind=0 ; ind<spritesQuantity ; ind++) {
        delete sprites[ind];
    }
    delete [] sprites;
}

void Stone::OnCollision(Object * obj) {
}

void Stone::Update() {
    if(durability == 0) GameLevel::GetScene()->Delete();
}

void Stone::Draw() {
    if(durability == 0) return;
    sprites[durability > 1]->Draw(x, y, Layer::UPPER);
}
