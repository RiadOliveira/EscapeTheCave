#ifndef _ESCAPETHECAVE_PLAYER_H_
#define _ESCAPETHECAVE_PLAYER_H_

#include "Types.h"
#include "Object.h"
#include "Sprite.h"
#include "Battery.h"

enum PLAYERSTATE {UP, DOWN, LEFT, RIGHT, NONE};    

class Player : public Object {
    private:
        Battery * battery = nullptr;

        Sprite * spriteUp = nullptr;
        Sprite * spriteDown = nullptr;
        Sprite * spriteLeft = nullptr;
        Sprite * spriteRight = nullptr;
        Image * &bombImage;

        float spriteSize;
        float speed = 120.0f;

        int bombsQuantity;
        PLAYERSTATE state;

        PLAYERSTATE GetStateBasedOnWindowKey();
        void HandleMovePlayer(PLAYERSTATE updatedState);
        void VerifyAndMovePlayerIfExceededWindow();
    public:
        Player(Image * &bombImage, Battery * battery);
        ~Player();

        float SpriteSize();
        float BatteryEnergy();
        PLAYERSTATE State();

        void OnCollision(Object * obj);
        void StoneCollision(Object * obj);

        void Update();
        void Draw();
};

inline float Player::SpriteSize() { return spriteSize; }
inline PLAYERSTATE Player::State() { return state; }

inline float Player::BatteryEnergy() { return battery->Energy(); }

#endif