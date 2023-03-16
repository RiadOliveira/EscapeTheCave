#ifndef _ESCAPETHECAVE_MININGPOINT_H_
#define _ESCAPETHECAVE_MININGPOINT_H_

#include "Object.h"
#include "Player.h"
#include "Stone.h"

class MiningPoint : public Object {
    private:
        Timer * breakTimer;
    
        float distanceToPlayer;
        Player * player = nullptr;
        Stone * collidingStone = nullptr;

        PLAYERSTATE previousState;
        uint GetBorderColor();
    public:
        MiningPoint(Player * player);
        ~MiningPoint();

        void OnCollision(Object * obj);
        void StoneCollision(Object * obj);

        void Update();
        void Draw();
};

#endif