#ifndef _ESCAPETHECAVE_Victory_H_
#define _ESCAPETHECAVE_Victory_H_

#include "Game.h"
#include "Sprite.h"

class Victory : public Game {
private:
    Sprite* backg = nullptr;
    Sprite* XKV8_4_Off = nullptr;
public:
    void Init();
    void Update();
    void Draw();
    void Finalize();
};

#endif