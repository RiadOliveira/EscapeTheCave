#ifndef _ESCAPETHECAVE_STONE_H_
#define _ESCAPETHECAVE_STONE_H_

#include "Types.h"
#include "Object.h"
#include "Sprite.h"
#include "Image.h"

class Stone : public Object {
    private:
        Sprite ** sprites = nullptr;
        Object * dropingItem = nullptr;

        static Image ** stoneImages;

        uint maxDurability, durability, spritesQuantity;
        float spriteSize;
    public:
        Stone(uint maxDurability);
        Stone(uint maxDurability, Object * dropingItem);
        ~Stone();

        uint Durability();
        uint MaxDurability();

        float SpriteSize();
        bool IsBroken();

        void Destroy();
        void DecreaseDurability();
        void OnCollision(Object * obj);

        void Update();
        void Draw();
};

inline uint Stone::Durability() { return durability; }
inline uint Stone::MaxDurability() { return maxDurability; }

inline float Stone::SpriteSize() { return spriteSize; }

inline void Stone::DecreaseDurability() { if(durability > 0) durability--; }
inline void Stone::Destroy() { durability = 0; }
inline bool Stone::IsBroken() { return durability == 0; }

#endif