#include "EscapeTheCave.h"
#include "Pivot.h"
#include "Bomb.h"
#include "Player.h"

Pivot::Pivot() {
    BBox(new Rect(-60, -60, 60, 60));
    type = PIVOT;
}

Pivot::~Pivot() {
}

void Pivot::OnCollision(Object * obj) {
    if(obj->Type() == PLAYER) PlayerCollision(obj);
    else if(obj->Type() == BOMB) BombCollision(obj);
}

void Pivot::PlayerCollision(Object * obj) {
    Player * player = (Player *) obj;

    float xDifference = abs(player->X() - x);
    float yDifference = abs(player->Y() - y);
    bool closeEnough = xDifference < 60 && yDifference < 60;

    if(!closeEnough) return;
    switch(player->State()) {
        case LEFT:
        case RIGHT: {
            bool needsToBeCentered = yDifference >= 0.1;
            if(needsToBeCentered) player->MoveTo(player->X(), y);
            break;
        }

        case UP:
        case DOWN: {
            bool needsToBeCentered = xDifference >= 0.1;
            if(needsToBeCentered) player->MoveTo(x, player->Y());
            break;
        }
    }
}

void Pivot::BombCollision(Object * obj) {
    bool needsToBeCentered = 
        abs(obj->X() - x) < 60 && abs(obj->Y() - y) < 60;
    if(needsToBeCentered) obj->MoveTo(x, y);
}