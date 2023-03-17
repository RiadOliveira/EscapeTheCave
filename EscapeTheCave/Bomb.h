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
        bool hasExploded, hasDecreasedPlayerEnergy;
        BOMBTYPE bombType;

        static Image * playedExplosionImage;
        static Image ** playedBombImages;
        static Image * generatedExplosionImage;
        static Image ** generatedBombImages;

        Timer * timer = nullptr;
        Sprite ** sprites = nullptr;

        void SetBombsAndExplosionImages();
    public:
        Bomb(BOMBTYPE bombType);
        ~Bomb();

        BOMBTYPE BombType();
    
        void OnCollision(Object * obj);
        void PlayerCollision(Object * obj);

        void Update();
        void Draw();
};

inline BOMBTYPE Bomb::BombType() { return bombType; }

#endif