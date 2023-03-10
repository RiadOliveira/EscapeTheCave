#ifndef _ESCAPETHECAVE_PLAYER_H_
#define _ESCAPETHECAVE_PLAYER_H_

#include "Types.h"
#include "Object.h"
#include "Sprite.h"

enum PLAYERSTATE {UP, DOWN, LEFT, RIGHT};    

class Player : public Object {
    private:
        Sprite * sprite = nullptr;
        PLAYERSTATE state = UP;
        float speed = 200.0f;
    public:
        Player();
        ~Player();

        void OnCollision(Object * obj);
        void PivotCollision(Object * obj);

        void Update();
        void Draw();
};

#endif