#ifndef _ESCAPETHECAVE_BATTERY_H_
#define _ESCAPETHECAVE_BATTERY_H_

#include "Types.h"
#include "Object.h"
#include "Sprite.h"
#include "Timer.h"

class Battery : public Object {
    private:
        static const float maxEnergy;
        static const uint spritesQuantity = 8;

        Timer * timer = nullptr;
        Sprite ** sprites = nullptr;
        uint selectedSpriteIndex;

        float timeOfOneBatteryBar;
        float energyOfOneBatteryBar;
        float energy;

        float GetXPosition();
        float GetYPosition();
    public:
        Battery();
        ~Battery();

        void RechargeBattery();
        void DecreaseEnergyBar();
        void BuffBatteryBarTime();
        void ResetDataToNewLevel();

        float Energy();
        float MaxEnergy();

        void OnCollision(Object * obj);

        void Update();
        void Draw();
};

inline void Battery::RechargeBattery() {
    energy = maxEnergy;
    selectedSpriteIndex = spritesQuantity - 1;
    timer->Reset();
}

inline void Battery::DecreaseEnergyBar() {
    if(selectedSpriteIndex == 0) {
        energy = 0.0f;
        return;
    }

    energy -= energyOfOneBatteryBar;
    selectedSpriteIndex--;
}

inline void Battery::BuffBatteryBarTime() {
    timeOfOneBatteryBar += 1.0f;
}

inline float Battery::GetXPosition() {
    return 16.0f + sprites[selectedSpriteIndex]->Width()/2;
}

inline float Battery::GetYPosition() {
    return 16.0f + sprites[selectedSpriteIndex]->Height()/2;
}

inline float Battery::Energy() { return energy; }
inline float Battery::MaxEnergy() { return maxEnergy; }

#endif