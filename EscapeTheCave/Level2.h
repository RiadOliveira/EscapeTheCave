#ifndef _ESCAPETHECAVE_LEVEl2_H_
#define _ESCAPETHECAVE_LEVEL2_H_

#include "Game.h"
#include "Sprite.h"
#include "Scene.h"

class Level2 : public Game {
    private:
        Sprite * backg = nullptr;
        Scene * scene = nullptr;
        bool viewBBox = false;
    public:
        void Init();
        void Update();
        void Draw();
        void Finalize();
};

#endif