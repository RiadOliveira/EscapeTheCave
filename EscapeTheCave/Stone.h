#ifndef _ESCAPETHECAVE_STONE_H_
#define _ESCAPETHECAVE_STONE_H_

#include "Types.h"
#include "Object.h"
#include "Sprite.h"
#include "Image.h"
#include "Bomb.h"

class Stone : public Object {
    private:
        Sprite ** sprites = nullptr;
        Object * dropingItem = nullptr;
        Bomb * collidingBomb = nullptr;

        static Image ** stoneImages;

        int maxDurability, durability, spritesQuantity;
        float spriteSize;

        void LoadStoneImages();
    public:
        Stone(int maxDurability);
        Stone(int maxDurability, Object * dropingItem);
        ~Stone();

        int Durability();
        int MaxDurability();

        float SpriteSize();
        bool IsBroken();

        void DecreaseDurability();
        void DecreaseDurabilityByMaxPercentage(float percentage);
        void OnCollision(Object * obj);

        void Update();
        void Draw();
};

inline int Stone::Durability() { return durability; }
inline int Stone::MaxDurability() { return maxDurability; }

inline float Stone::SpriteSize() { return spriteSize; }
inline void Stone::DecreaseDurability() { if(durability > 0) durability--; }

inline bool Stone::IsBroken() { return durability == 0; }

#endif