#ifndef _ESCAPETHECAVE_GENERATOR_H_
#define _ESCAPETHECAVE_GENERATOR_H_

#include "Types.h"
#include "Object.h"
#include "Sprite.h"
#include "Timer.h"

class Generator : public Object {
    private:
        Sprite * sprite = nullptr;
        Timer * timer = nullptr;
        
        bool playerHasEscaped;
    public:
        Generator(int level);
        ~Generator();

        bool PlayerHasEscaped();
        void OnCollision(Object * obj);

        void Update();
        void Draw();
};

inline bool Generator::PlayerHasEscaped() { return playerHasEscaped; }

#endif