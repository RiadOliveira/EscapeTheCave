#ifndef _ESCAPETHECAVE_LEVEl1_H_
#define _ESCAPETHECAVE_LEVEL1_H_

#include "Game.h"
#include "Sprite.h"

class Level1 : public Game {
    private:
        Sprite * backg = nullptr;
        bool viewBBox = false;

        Image * stoneImage;
        Image * mossStoneImage;
        Image * bombImage;

        void RenderLevelStonesAndPivots();
        void CreateLevelStoneOrPivot(
            float positionX, float positionY
        );
    public:
        void Init();
        void Update();
        void Draw();
        void Finalize();
};

#endif