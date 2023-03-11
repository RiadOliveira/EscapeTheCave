#ifndef _ESCAPETHECAVE_BATTERY_H_
#define _ESCAPETHECAVE_BATTERY_H_

#include "Types.h"
#include "Object.h"
#include "Sprite.h"
#include "Player.h"

class Battery : public Object {
    private:
        static const uint spritesQuantity = 8;

        Player * player = nullptr;
        Sprite ** sprites = nullptr;
        uint selectedSpriteIndex;
        float energyOfOneBatteryBar;

        int GetXPosition();
        int GetYPosition();
    public:
        Battery(Player * player);
        ~Battery();

        void OnCollision(Object * obj);

        void Update();
        void Draw();
};

inline int Battery::GetXPosition() {
    return 16.0f + sprites[selectedSpriteIndex]->Width()/2;
}

inline int Battery::GetYPosition() {
    return 16.0f + sprites[selectedSpriteIndex]->Height()/2;
}

#endif