#ifndef _ESCAPETHECAVE_BOMB_H_
#define _ESCAPETHECAVE_BOMB_H_

#include "Object.h"
#include "Sprite.h"
#include "Timer.h"

enum BOMBTYPE { PLAYED, GENERATED };

class Bomb : public Object {
    private:
        bool hasExploded;

        static Image * explosionImage;
        Timer * timer = nullptr;

        Sprite * sprite = nullptr;
        BOMBTYPE bombType;
    public:
        Bomb(BOMBTYPE bombType, Image * image);
        ~Bomb();

        void OnCollision(Object * obj);
        void StoneCollision(Object * obj);
        void PlayerCollision(Object * obj);

        void Update();
        void Draw();
};

#endif