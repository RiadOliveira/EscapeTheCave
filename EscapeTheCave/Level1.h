#ifndef _ESCAPETHECAVE_LEVEl1_H_
#define _ESCAPETHECAVE_LEVEL1_H_

#include "Game.h"
#include "Sprite.h"
#include "Scene.h"

class Level1 : public Game {
    private:
        Sprite * backg = nullptr;
        Scene * scene = nullptr;
        Image * stoneImage = nullptr;
        bool viewBBox = false;

        void RenderLevelStones();
        void CreateLevelStone(
            int positionX, int positionY
        );
    public:
        void Init();
        void Update();
        void Draw();
        void Finalize();
};

#endif