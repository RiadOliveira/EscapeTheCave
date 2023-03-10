#include "EscapeTheCave.h"
#include "Pivot.h"

Pivot::Pivot(bool l, bool r, bool u, bool d) {
    left  = l;
    right = r;
    up    = u;
    down  = d;

    BBox(new Rect(-4, -4, 4, 4));
    type = PIVOT;
}

Pivot::~Pivot() {
}
