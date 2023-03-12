#ifndef _ESCAPETHECAVE_PIVOT_H_
#define _ESCAPETHECAVE_PIVOT_H_

#include "Types.h"                         
#include "Object.h"                        

class Pivot : public Object {
    public:
        Pivot();
        ~Pivot();

        void OnCollision(Object * obj);
        void PlayerCollision(Object * obj);
        void BombCollision(Object * obj);

        void Update() {};
        void Draw() {};
};

#endif