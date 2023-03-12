#include "EscapeTheCave.h"
#include "Pivot.h"

Pivot::Pivot() {
    BBox(new Rect(-60, -60, 60, 60));
    type = PIVOT;
}

Pivot::~Pivot() {
}
