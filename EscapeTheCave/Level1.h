#ifndef _ESCAPETHECAVE_LEVEl1_H_
#define _ESCAPETHECAVE_LEVEL1_H_

#include "Game.h"
#include "Player.h"
#include "Sprite.h"

class Level1 : public Game {
    private:
        Sprite * backg = nullptr;
        bool viewBBox = false;

        Player * player = nullptr;
        Image * stoneImage = nullptr;
        Image * mossStoneImage = nullptr;
        Image * bombImage = nullptr;

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