#include "MiningPoint.h"
#include "EscapeTheCave.h"
#include "Stone.h"
#include "Game.h"
#include "Engine.h"

MiningPoint::MiningPoint(Player * player): 
    player(player), previousState(player->State()),
    distanceToPlayer(player->SpriteSize()/2 + 16.0f)
{
    BBox(new Point(player->X(), player->Y()));
    type = MINING_POINT;
}

MiningPoint::~MiningPoint() {
}

void MiningPoint::OnCollision(Object * obj) {
    if(obj->Type() == STONE) StoneCollision(obj);
}

void MiningPoint::StoneCollision(Object * obj) {
    Stone * stone = (Stone *) obj;
    
    if(window->KeyPress(VK_SPACE) || window->KeyPress(VK_LBUTTON)){
        stone->DecreaseDurability();
        collidingStone = nullptr;
    } else collidingStone = stone;
}

void MiningPoint::Update() {
    PLAYERSTATE updatedState = player->State();

    bool needsToRemoveStoneReference = collidingStone != nullptr &&
        (previousState != updatedState || collidingStone->IsBroken());
    if(needsToRemoveStoneReference) collidingStone = nullptr;

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
