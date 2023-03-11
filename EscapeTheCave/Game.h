#ifndef _GAME_H_
#define _GAME_H_

#include "Window.h"
#include "Scene.h"

class Game {
    protected:
        static Window* & window;
        static float   & gameTime;
        static Scene*  scene;
    public:
        Game();
        virtual ~Game();
        
        static Scene* GetScene();
        virtual void OnPause();

        virtual void Init() = 0;
        virtual void Update() = 0;
        virtual void Draw() = 0;
        virtual void Finalize() = 0;
};

inline Scene* Game::GetScene() { return scene; }

#endif