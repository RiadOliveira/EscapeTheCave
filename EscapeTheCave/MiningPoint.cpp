#include "MiningPoint.h"
#include "EscapeTheCave.h"
#include "Stone.h"
#include "GameLevel.h"
#include "Engine.h"

MiningPoint::MiningPoint(): 
    player(GameLevel::GetPlayer()),
    previousState(player->State()),
    distanceToPlayer(player->SpriteSize()/2 + 16.0f)
{
    BBox(new Point(player->X(), player->Y()));
    type = MINING_POINT;
    breakTimer = new Timer();
}

MiningPoint::~MiningPoint() {
    delete breakTimer;
}

void MiningPoint::OnCollision(Object * obj) {
    if(obj->Type() == STONE) StoneCollision(obj);
}

void MiningPoint::StoneCollision(Object * obj) {
    Stone * stone = (Stone *) obj;
    bool isBreakingStone = window->KeyDown(VK_SPACE) || window->KeyDown(VK_LBUTTON);

    if(collidingStone != stone || !isBreakingStone) {
        collidingStone = stone;
        breakTimer->Reset();
        return;
    }

    if(breakTimer->Elapsed() >= player->MiningSpeed()) {
        stone->DecreaseDurability();
        if(stone->IsBroken()) collidingStone = nullptr;

        breakTimer->Reset();
    }
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
    if(collidingStone == nullptr) return;

    Engine::renderer->BeginPixels();
    Engine::renderer->Draw(
        collidingStone->BBox(), 0xffffffff
    );
    Engine::renderer->EndPixels();
}
