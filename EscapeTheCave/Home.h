#ifndef _ESCAPETHECAVE_HOME_H_
#define _ESCAPETHECAVE_HOME_H_

#include "Game.h"
#include "Sprite.h"


class Home : public Game {
    private:
        Sprite * backg = nullptr;
    public:
        void Init();
        void Update();
        void Draw();
        void Finalize();
};

#endif