#ifndef _ESCAPETHECAVE_PLAYER_H_
#define _ESCAPETHECAVE_PLAYER_H_

#include "Types.h"
#include "Object.h"
#include "Sprite.h"

enum PLAYERSTATE {UP, DOWN, LEFT, RIGHT, NONE};    

class Player : public Object {
    private:
        Sprite * spriteUp = nullptr;
        Sprite * spriteDown = nullptr;
        Sprite * spriteLeft = nullptr;
        Sprite * spriteRight = nullptr;

        int spriteSize;
        PLAYERSTATE state;
        float speed = 200.0f;

        PLAYERSTATE GetStateBasedOnWindowKey();
        void HandleMovePlayer(PLAYERSTATE updatedState);
        void VerifyAndMovePlayerIfExceededWindow();
    public:
        Player();
        ~Player();

        void OnCollision(Object * obj);
        void PivotCollision(Object * obj);

        void Update();
        void Draw();

        PLAYERSTATE State();
        int SpriteSize();
};

inline PLAYERSTATE Player::State() { return state; }
inline int Player::SpriteSize() { return spriteSize; }

#endif