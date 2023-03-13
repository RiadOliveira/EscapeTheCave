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

uint MiningPoint::GetBorderColor() {
    uint whiteColor = 0xffffffff;
    if(collidingStone->MaxDurability() == 1) {
        return whiteColor;
    }

    float durabilityProportion = 
        (float) collidingStone->Durability() /
        (float) collidingStone->MaxDurability();

    if(durabilityProportion <= 0.5f) return whiteColor;
    if(durabilityProportion <= 0.6f) return 0xff555555;
    if(durabilityProportion <= 0.8f) return 0xff333333;
    if(durabilityProportion <= 0.9f) return 0xff111111;
    return 0xff000000;
}

void MiningPoint::Draw() {
    if(!collidingStone) return;

    Engine::renderer->BeginPixels();
    Engine::renderer->Draw(
        collidingStone->BBox(), GetBorderColor()
    );
    Engine::renderer->EndPixels();
}
