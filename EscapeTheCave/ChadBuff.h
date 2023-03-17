#ifndef _ESCAPETHECAVE_CHAD_BUFF_H_
#define _ESCAPETHECAVE_CHAD_BUFF_H_

#include "Types.h"
#include "Object.h"
#include "Sprite.h"
#include "Image.h"

class ChadBuff : public Object {
    private:
        static Image * image;
        Sprite * sprite = nullptr;

        bool hasToBeDestroyed;
    public:
        ChadBuff();
        ~ChadBuff();

        void OnCollision(Object * obj);

        void Update();
        void Draw();
};

#endif