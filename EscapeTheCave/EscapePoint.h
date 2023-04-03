#ifndef _ESCAPETHECAVE_ESCAPE_POINT_H_
#define _ESCAPETHECAVE_ESCAPE_POINT_H_

#include "Types.h"
#include "Object.h"
#include "Sprite.h"
#include "Timer.h"

class EscapePoint : public Object {
    private:
        Sprite * sprite = nullptr;
        Timer * timer = nullptr;
    public:
        EscapePoint(bool finalEscape);
        ~EscapePoint();

        void OnCollision(Object * obj);

        void Update();
        void Draw();
};

#endif