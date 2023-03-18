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
        Sprite ** bombButtonIcons = nullptr;
        Sprite ** radarButtonIcons = nullptr;

        bool hasGeneratedChadBuff = false;
        bool viewBBox = false;

        static Player* player;
        static Scene* scene;
        static int* escapePoint;

        int* GenerateEscapePoint();
        bool HasCreatedPivot(float positionX, float positionY);

        Object * GenerateDroppableItem(int generatedNumber);
        void RenderLevelStonesAndPivots();
        void CreateLevelStoneOrPivot(
            float positionX, float positionY,
            bool isEscapePoint
        );
    public:
        static Player* &GetPlayer();
        static Scene* &GetScene();
        static int* &GetEscapePoint();

        void Init();
        void Update();
        void Draw();
        void Finalize();
};

inline Player* &GameLevel::GetPlayer() { return player; }
inline Scene* &GameLevel::GetScene() { return scene; }
inline int* &GameLevel::GetEscapePoint() { return escapePoint; }

#endif