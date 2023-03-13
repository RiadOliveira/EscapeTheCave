#ifndef _ESCAPETHECAVE_LEVEl2_H_
#define _ESCAPETHECAVE_LEVEL2_H_

#include "Game.h"
#include "Player.h"
#include "Sprite.h"
#include "random"

using std::random_device;

class Level2 : public Game {
    private:
        random_device rd;
        static const uint objectDefaultWidth = 120;

        Sprite * backg = nullptr;
        Player * player = nullptr;
        bool viewBBox = false;

        int * GetEscapePoint();
        bool HasCreatedPivot(float positionX, float positionY);

        void RenderLevelStonesAndPivots();
        void CreateLevelStoneOrPivot(
            float positionX, float positionY,
            bool isEscapePoint
        );
    public:
        void Init();
        void Update();
        void Draw();
        void Finalize();
};

#endif