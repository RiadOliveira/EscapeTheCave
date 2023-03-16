#ifndef _ESCAPETHECAVE_GameLevel_H_
#define _ESCAPETHECAVE_GameLevel_H_

#include "Game.h"
#include "Sprite.h"
#include "random"
#include "Player.h"

using std::random_device;

class GameLevel : public Game {
    private:
        random_device rd;
        static const uint objectDefaultWidth = 120;

        Sprite * backg = nullptr;
        bool viewBBox = false;

        static uint level;
        static Player* player;
        static Scene* scene;

        int * GetEscapePoint();
        bool HasCreatedPivot(float positionX, float positionY);

        void RenderLevelStonesAndPivots();
        void CreateLevelStoneOrPivot(
            float positionX, float positionY,
            bool isEscapePoint
        );
    public:
        static Scene* GetScene();

        void Init();
        void Update();
        void Draw();
        void Finalize();
};

inline Scene* GameLevel::GetScene() { return scene; }

#endif