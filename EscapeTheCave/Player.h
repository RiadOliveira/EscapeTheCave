#ifndef _ESCAPETHECAVE_PLAYER_H_
#define _ESCAPETHECAVE_PLAYER_H_

#include "Types.h"
#include "Object.h"
#include "Sprite.h"

enum PLAYERSTATE {UP, DOWN, LEFT, RIGHT, NONE};    

class Player : public Object {
    private:
        float maxEnergy = 100.0f;

        Sprite * spriteUp = nullptr;
        Sprite * spriteDown = nullptr;
        Sprite * spriteLeft = nullptr;
        Sprite * spriteRight = nullptr;
        Image * &bombImage;

        float spriteSize;
        float speed = 120.0f;
        float energy = 100.0f;

        int bombsQuantity;
        PLAYERSTATE state;

        PLAYERSTATE GetStateBasedOnWindowKey();
        void HandleMovePlayer(PLAYERSTATE updatedState);
        void VerifyAndMovePlayerIfExceededWindow();
    public:
        Player(Image * &bombImage);
        ~Player();

        float SpriteSize();
        PLAYERSTATE State();
        float Energy();
        float MaxEnergy();

        void OnCollision(Object * obj);
        void StoneCollision(Object * obj);

        void Update();
        void Draw();
};

inline float Player::SpriteSize() { return spriteSize; }
inline float Player::Energy() { return energy; }
inline float Player::MaxEnergy() { return maxEnergy; }

inline PLAYERSTATE Player::State() { return state; }

#endif