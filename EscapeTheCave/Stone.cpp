#include "Stone.h"
#include "Player.h"
#include "EscapeTheCave.h"

Stone::Stone(Image * stoneImage) {
    sprite = new Sprite(stoneImage);
    
    BBox(new Rect(-32, -32, 32, 32));
    type = STONE;
}

Stone::~Stone() {
    delete sprite;
}

void Stone::OnCollision(Object * obj) {
    if(obj->Type() == PLAYER) OnPlayerCollision(obj);
}

void Stone::OnPlayerCollision(Object * obj) {
    Player * player = (Player*) obj;
    PLAYERSTATE playerState = player->State();
    int playerSpriteSize = player->SpriteSize();

    switch(playerState) {
        case UP:
        case DOWN: {
            float directionModifier = 
                (playerSpriteSize + .1) * (playerState == UP ? 1 : -1);
                
            player->MoveTo(player->X(), Y() + directionModifier);
            break;
        }

        case LEFT:
        case RIGHT: {
            float directionModifier = 
                (playerSpriteSize + .1) * (playerState == LEFT ? 1 : -1);

            player->MoveTo(X() + directionModifier, player->Y());
            break;
        }
    }
}

void Stone::Update() {
}

void Stone::Draw() {
    sprite->Draw(x, y, Layer::UPPER);
}
