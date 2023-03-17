#ifndef _ESCAPETHECAVE_MINING_BUFF_H_
#define _ESCAPETHECAVE_MINING_BUFF_H_

#include "Types.h"
#include "Object.h"
#include "Sprite.h"
#include "Image.h"

class MiningBuff : public Object {
    private:
        static Image * image;
        Sprite * sprite = nullptr;

        bool hasToBeDestroyed;
    public:
        MiningBuff();
        ~MiningBuff();

        void OnCollision(Object * obj);

        void Update();
        void Draw();
};

#endif