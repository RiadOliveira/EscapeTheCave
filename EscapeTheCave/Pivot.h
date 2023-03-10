#ifndef _ESCAPETHECAVE_PIVOT_H_
#define _ESCAPETHECAVE_PIVOT_H_

#include "Types.h"                         
#include "Object.h"                        

class Pivot : public Object {
    public:
        bool left  = false;
        bool right = false;
        bool up    = false;
        bool down  = false;

        Pivot(bool l, bool r, bool u, bool d);
        ~Pivot(); 

        void Update() {};
        void Draw() {};
};

#endif