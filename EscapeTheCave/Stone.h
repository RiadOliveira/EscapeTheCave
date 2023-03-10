#ifndef _ESCAPETHECAVE_STONE_H_
#define _ESCAPETHECAVE_STONE_H_

#include "Types.h"
#include "Object.h"
#include "Sprite.h"

class Stone : public Object {
    private:
        Sprite * sprite = nullptr;
    public:
        Stone(Image * stoneImage);
        ~Stone();

        void OnCollision(Object * obj);

        void Update();
        void Draw();
};

#endif