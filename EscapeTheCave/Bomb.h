#ifndef _ESCAPETHECAVE_BOMB_H_
#define _ESCAPETHECAVE_BOMB_H_

#include "Object.h"
#include "Sprite.h"
#include "Timer.h"

enum BOMBTYPE { PLAYED, GENERATED };
enum BOMBSTATES { INITIAL, EXPLODING, EXPLODED };

class Bomb : public Object {
    private:
        float previousElapsedTime;

        BOMBSTATES selectedSpriteState;
        bool hasExploded;
        BOMBTYPE bombType;

        static Image * explosionImage;
        static Image ** bombImages;

        Timer * timer = nullptr;
        Sprite ** sprites = nullptr;
    public:
        Bomb(BOMBTYPE bombType);
        ~Bomb();

        void OnCollision(Object * obj);
        void StoneCollision(Object * obj);
        void PlayerCollision(Object * obj);

        void Update();
        void Draw();
};

#endif