#ifndef _ESCAPETHECAVE_MININGPOINT_H_
#define _ESCAPETHECAVE_MININGPOINT_H_

#include "Object.h"
#include "Player.h"
#include "Stone.h"

class MiningPoint : public Object {
    private:
        float distanceToPlayer;
        Player * player = nullptr;
        Stone * collidingStone = nullptr;

        PLAYERSTATE previousState;
    public:
        MiningPoint(Player * player);
        ~MiningPoint();

        void OnCollision(Object * obj);
        void StoneCollision(Object * obj);

        void Update();
        void Draw();
};

#endif