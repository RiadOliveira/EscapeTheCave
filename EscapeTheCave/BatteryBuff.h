#ifndef _ESCAPETHECAVE_BATTERY_BUFF_H_
#define _ESCAPETHECAVE_BATTERY_BUFF_H_

#include "Types.h"
#include "Object.h"
#include "Sprite.h"
#include "Image.h"

class BatteryBuff : public Object {
    private:
        static Image * image;
        Sprite * sprite = nullptr;

        bool hasToBeDestroyed;
    public:
        BatteryBuff();
        ~BatteryBuff();

        void OnCollision(Object * obj);

        void Update();
        void Draw();
};

#endif