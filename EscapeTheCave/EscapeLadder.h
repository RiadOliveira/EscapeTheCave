#ifndef _ESCAPETHECAVE_ESCAPELADDER_H_
#define _ESCAPETHECAVE_ESCAPELADDER_H_

#include "Types.h"
#include "Object.h"
#include "Sprite.h"
#include "Image.h"
#include "Timer.h"

class EscapeLadder : public Object {
    private:
        Sprite * sprite = nullptr;
        Timer * timer = nullptr;
        
        bool playerHasEscaped;
    public:
        EscapeLadder();
        ~EscapeLadder();

        bool PlayerHasEscaped();
        void OnCollision(Object * obj);

        void Update();
        void Draw();
};

inline bool EscapeLadder::PlayerHasEscaped() { return playerHasEscaped; }

#endif