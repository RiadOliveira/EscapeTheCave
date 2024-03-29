#ifndef _ESCAPETHECAVE_SPEED_BUFF_H_
#define _ESCAPETHECAVE_SPEED_BUFF_H_

#include "Types.h"
#include "Object.h"
#include "Sprite.h"
#include "Image.h"

class SpeedBuff : public Object {
    private:
        static Image * image;
        Sprite * sprite = nullptr;

        bool hasToBeDestroyed;
    public:
        SpeedBuff();
        ~SpeedBuff();

        void OnCollision(Object * obj);

        void Update();
        void Draw();
};

#endif