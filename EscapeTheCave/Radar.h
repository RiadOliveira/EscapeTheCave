#ifndef _ESCAPETHECAVE_RADAR_H_
#define _ESCAPETHECAVE_RADAR_H_

#include "Types.h"
#include "Object.h"
#include "Sprite.h"
#include "Timer.h"

enum RadarState { RADAR_UP, RADAR_DOWN, RADAR_LEFT, RADAR_RIGHT, DISABLED };

class Radar : public Object {
    private:
        static const uint spritesQuantity = 4;

        bool showingRadar;
        float previousElapsedTime;
        uint radarDirection;

        Timer * timer = nullptr;
        Sprite ** sprites = nullptr;
    public:
        Radar();
        ~Radar();

        bool IsOnCooldown();

        void ActivateRadar();
        void ResetDataToNewLevel();
        void OnCollision(Object * obj);

        void Update();
        void Draw();
};

inline bool Radar::IsOnCooldown() { return radarDirection != DISABLED; }

#endif