#include "MiningPoint.h"
#include "EscapeTheCave.h"
#include "Stone.h"
#include "Game.h"
#include "Engine.h"

MiningPoint::MiningPoint(Player * player): 
    player(player), previousState(player->State()),
    distanceToPlayer(player->SpriteSize()/2 + 16)
{
    BBox(new Point(player->X(), player->Y()));
}

MiningPoint::~MiningPoint() {
}

void MiningPoint::OnCollision(Object * obj) {
    if(obj->Type() == STONE) StoneCollision(obj);
}

void MiningPoint::StoneCollision(Object * obj) {
    Stone * stone = (Stone *) obj;

    if(window->KeyPress(VK_SPACE)) {
        collidingStone = nullptr;
        stone->DecreaseDurability();
    } else collidingStone = stone;
}

void MiningPoint::Update() {
    PLAYERSTATE updatedState = player->State();
    if(previousState != updatedState) collidingStone = nullptr;

    switch(updatedState) {
        case LEFT: {
            MoveTo(player->X() - distanceToPlayer, player->Y());
            break;
        }
        case RIGHT: {
            MoveTo(player->X() + distanceToPlayer, player->Y());
            break;
        }
        case UP: {
            MoveTo(player->X(), player->Y() - distanceToPlayer);
            break;
        }
        case DOWN: {
            MoveTo(player->X(), player->Y() + distanceToPlayer);
            break;
        }
    }

    previousState = updatedState;
}

void MiningPoint::Draw() {
    if(!collidingStone) return;

    Engine::renderer->BeginPixels();
    Engine::renderer->Draw(collidingStone->BBox(), 0xffffffff);
    Engine::renderer->EndPixels();
}
