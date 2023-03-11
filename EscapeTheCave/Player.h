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
        float speed = 160.0f;

        PLAYERSTATE GetStateBasedOnWindowKey();
        void HandleMovePlayer(PLAYERSTATE updatedState);
        void VerifyAndMovePlayerIfExceededWindow();
    public:
        Player();
        ~Player();

        int SpriteSize();
        PLAYERSTATE State();

        void OnCollision(Object * obj);
        void StoneCollision(Object * obj);

        void Update();
        void Draw();
};

inline int Player::SpriteSize() { return spriteSize; }
inline PLAYERSTATE Player::State() { return state; }

#endif