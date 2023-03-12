#ifndef _ESCAPETHECAVE_LEVEl1_H_
#define _ESCAPETHECAVE_LEVEL1_H_

#include "Game.h"
#include "Sprite.h"

class Level1 : public Game {
    private:
        Sprite * backg = nullptr;
        Image * stoneImage = nullptr;
        Image * mossStoneImage = nullptr;
        bool viewBBox = false;

        void RenderLevelStones();
        void CreateLevelStone(
            float positionX, float positionY
        );
    public:
        void Init();
        void Update();
        void Draw();
        void Finalize();
};

#endif