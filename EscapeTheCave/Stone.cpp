#include "Stone.h"
#include "Player.h"
#include "Game.h"
#include "EscapeTheCave.h"

Stone::Stone(Image ** images, uint spritesQuantity):
    spriteSize(images[0]->Width()), spritesQuantity(spritesQuantity),
    durability(spritesQuantity)
{
    sprites = new Sprite*[spritesQuantity];
    for(int ind=0 ; ind<spritesQuantity ; ind++) {
        sprites[ind] = new Sprite(images[ind]);
    }

    BBox(new Rect(-60, -60, 60, 60));
    type = STONE;
}

Stone::Stone(Image ** images, uint spritesQuantity, Object * dropingItem):
    Stone(images, spritesQuantity)
{
    this->dropingItem = dropingItem;
}

Stone::~Stone() {
    if(dropingItem) {
        dropingItem->MoveTo(x, y);
        Game::GetScene()->Add(dropingItem, STATIC);
    }

    for(int ind=0 ; ind<spritesQuantity ; ind++) {
        delete sprites[ind];
    }
    delete [] sprites;
}

void Stone::OnCollision(Object * obj) {
}

void Stone::Update() {
    if(durability == 0) Game::GetScene()->Delete();
}

void Stone::Draw() {
    if(durability == 0) return;
    sprites[durability - 1]->Draw(x, y, Layer::UPPER);
}
