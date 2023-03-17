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
        Image* stone0 = new Image("Resources/Stone/Stone0.png");
        Image* stone1 = new Image("Resources/Stone/Stone1.png");
        Image* stone2 = new Image("Resources/Stone/Stone2.png");
        Image* stone3 = new Image("Resources/Stone/Stone3.png");

        stoneImages = new Image*[4]{stone0, stone1, stone2, stone3};
    }

    spritesQuantity = maxDurability > 4 ? 4 : maxDurability;
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
        GameLevel::GetScene()->Add(dropingItem, MOVING);
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

    float durabilityProportion = (float) durability / (float) maxDurability;
    int spritePosition = durabilityProportion * (spritesQuantity - 1);

    sprites[spritePosition]->Draw(x, y, Layer::UPPER);
}
