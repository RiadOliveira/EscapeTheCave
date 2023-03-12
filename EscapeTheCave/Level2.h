#ifndef _ESCAPETHECAVE_LEVEl2_H_
#define _ESCAPETHECAVE_LEVEL2_H_

#include "Game.h"
#include "Sprite.h"

class Level2 : public Game {
    private:
        Sprite * backg = nullptr;
        bool viewBBox = false;

        Image * stoneImage;
        Image * mossStoneImage;
        Image * bombImage;

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