#ifndef _ESCAPETHECAVE_STONE_H_
#define _ESCAPETHECAVE_STONE_H_

#include "Types.h"
#include "Object.h"
#include "Sprite.h"

class Stone : public Object {
    private:
        Sprite ** sprites = nullptr;
        Object * dropingItem = nullptr;

        uint spritesQuantity, durability;
        float spriteSize;
    public:
        Stone(Image ** images, uint spritesQuantity);
        Stone(Image ** images, uint spritesQuantity, Object * dropingItem);
        ~Stone();

        float SpriteSize();

        void DecreaseDurability();
        void OnCollision(Object * obj);

        void Update();
        void Draw();
};

inline float Stone::SpriteSize() { return spriteSize; }
inline void Stone::DecreaseDurability() { durability--; }

#endif