#ifndef _ESCAPETHECAVE_GAMEOVER_H_
#define _ESCAPETHECAVE_GAMEOVER_H_

#include "Game.h"
#include "Sprite.h"

class GameOver : public Game {
    private:
        Sprite * backg = nullptr;
        Sprite * XKV8_4_Off = nullptr;
    public:
        void Init();
        void Update();
        void Draw();
        void Finalize();
};

#endif