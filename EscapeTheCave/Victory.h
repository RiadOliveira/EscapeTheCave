#ifndef _ESCAPETHECAVE_VICTORY_H_
#define _ESCAPETHECAVE_VICTORY_H_

#include "Game.h"
#include "Sprite.h"

class Victory : public Game {
    private:
        Sprite* backg = nullptr;
    public:
        void Init();
        void Update();
        void Draw();
        void Finalize();
};

#endif