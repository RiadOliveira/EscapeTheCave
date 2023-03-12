#ifndef _ESCAPETHECAVE_PIVOT_H_
#define _ESCAPETHECAVE_PIVOT_H_

#include "Types.h"                         
#include "Object.h"                        

class Pivot : public Object {
    public:
        Pivot();
        ~Pivot(); 

        void Update() {};
        void Draw() {};
};

#endif