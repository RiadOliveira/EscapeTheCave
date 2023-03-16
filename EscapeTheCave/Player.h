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

        float spriteSize;
        float speed;
        float miningSpeed;

        bool playerHasEscaped;
        int bombsQuantity;
        PLAYERSTATE state;

        PLAYERSTATE GetStateBasedOnWindowKey();
        void HandleMovePlayer(PLAYERSTATE updatedState);
        void VerifyAndMovePlayerIfExceededWindow();
    public:
        Player(Battery * battery);
        ~Player();

        Battery * GetBattery();
        void ResetDataToNewLevel();

        bool PlayerHasEscaped();
        void PlayerHasEscaped(bool hasEscaped);

        float SpriteSize();
        float BatteryEnergy();
        PLAYERSTATE State();

        void OnCollision(Object * obj);
        void StoneCollision(Object * obj);

        void Update();
        void Draw();
};

inline Battery* Player::GetBattery() { return battery; }

inline bool Player::PlayerHasEscaped() { return playerHasEscaped; }
inline void Player::PlayerHasEscaped(bool hasEscaped) {
    playerHasEscaped = hasEscaped;
}

inline float Player::SpriteSize() { return spriteSize; }
inline PLAYERSTATE Player::State() { return state; }

inline float Player::BatteryEnergy() { return battery->Energy(); }

#endif