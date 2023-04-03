#include "Stone.h"
#include "Player.h"
#include "GameLevel.h"
#include "Pivot.h"
#include "EscapeTheCave.h"

Image ** Stone::stoneImages = nullptr;

void Stone::LoadStoneImages() {
    if(stoneImages != nullptr) return;

    Image* stone0 = new Image("Resources/Stone/Stone0.png");
    Image* stone1 = new Image("Resources/Stone/Stone1.png");
    Image* stone2 = new Image("Resources/Stone/Stone2.png");
    Image* stone3 = new Image("Resources/Stone/Stone3.png");
    Image* stone4 = new Image("Resources/Stone/Stone4.png");
    Image* stone5 = new Image("Resources/Stone/Stone5.png");
    Image* stone6 = new Image("Resources/Stone/Stone6.png");
    Image* stone7 = new Image("Resources/Stone/Stone7.png");
    Image* stone8 = new Image("Resources/Stone/Stone8.png");
    Image* stone9 = new Image("Resources/Stone/Stone9.png");

    stoneImages = new Image*[10]{
        stone0, stone1, stone2, stone3, stone4,
        stone5, stone6, stone7, stone8, stone9
    };
}

Stone::Stone(int maxDurability):
    maxDurability(maxDurability), durability(maxDurability)
{
    LoadStoneImages();

    spritesQuantity = maxDurability > 10 ? 10 : maxDurability;
    sprites = new Sprite*[spritesQuantity];
    for(int ind=0 ; ind<spritesQuantity ; ind++) {
        sprites[ind] = new Sprite(stoneImages[ind]);
    }

    spriteSize = (float) stoneImages[0]->Width();
    float boxCoord = spriteSize/2;

    BBox(new Rect(-boxCoord, -boxCoord, boxCoord, boxCoord));
    type = STONE;
}

Stone::Stone(int maxDurability, Object * dropingItem):
    Stone(maxDurability)
{
    this->dropingItem = dropingItem;
}

Stone::~Stone() {
    if(dropingItem) {
        int parsedType = dropingItem->Type() == BOMB ? MOVING : STATIC;

        dropingItem->MoveTo(x, y);
        GameLevel::GetScene()->Add(dropingItem, parsedType);
    }

    Pivot * pivot = new Pivot();
    pivot->MoveTo(x, y);
    GameLevel::GetScene()->Add(pivot, STATIC);

    for(int ind=0 ; ind<spritesQuantity ; ind++) {
        delete sprites[ind];
    }
    delete [] sprites;
}

void Stone::DecreaseDurabilityByMaxPercentage(float percentage) {
    if(durability == 0) return;
    int durabilityReduction = (int) ceil(percentage * (float) maxDurability);

    durability -= durabilityReduction;
    durability = durability <= 0 ? 0 : durability;
}

void Stone::OnCollision(Object * obj) {
    if(obj->Type() != BOMB) return;
    
    Bomb * bomb = (Bomb *) obj;
    if(bomb == collidingBomb || bomb->BombType() == GENERATED) return;

    DecreaseDurabilityByMaxPercentage(0.75f);
    collidingBomb = bomb;
}

void Stone::Update() {
    if(durability == 0) GameLevel::GetScene()->Delete();
}

void Stone::Draw() {
    if(durability == 0) return;

    float durabilityProportion = (float) durability / (float) maxDurability;
    int spritePosition = (int) (durabilityProportion * (spritesQuantity - 1));

    sprites[spritePosition]->Draw(x, y, Layer::LOWER);
}
