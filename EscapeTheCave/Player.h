#ifndef _ESCAPETHECAVE_PLAYER_H_
#define _ESCAPETHECAVE_PLAYER_H_

#include "Types.h"
#include "Object.h"
#include "Sprite.h"
#include "Battery.h"
#include "Radar.h"

enum PLAYERSTATE { UP, DOWN, LEFT, RIGHT, NONE };

class Player : public Object {
    private:
        Battery * battery = nullptr;
        Radar * radar = nullptr;

        Sprite ** sprites = nullptr;
        Sprite ** gentleBotSprites = nullptr;

        float spriteSize;
        float speed;

        const float maxMiningSpeed = 0.1f;
        float miningSpeed;

        bool gentleBotMode;
        bool playerHasEscaped;

        int bombsQuantity;
        PLAYERSTATE state;

        PLAYERSTATE GetStateBasedOnWindowKey();
        void HandleMovePlayer(PLAYERSTATE updatedState);
        void VerifyAndMovePlayerIfExceededWindow();
        void SetPlayerSprites();
    public:
        Player();
        ~Player();

        Battery * GetBattery();
        void ResetDataToNewLevel(int levelBombsQuantity);
        void ActivateGentleBotMode();

        void AddToScene();
        void RemoveFromScene();

        void BuffSpeed();
        void BuffMiningSpeed();
        void BuffBatteryTime();

        bool PlayerHasEscaped();
        void PlayerHasEscaped(bool hasEscaped);

        float MiningSpeed();
        float SpriteSize();
        float BatteryEnergy();
        PLAYERSTATE State();

        int HasBombs();
        bool RadarIsOnCooldown();

        void OnCollision(Object * obj);
        void StoneCollision(Object * obj);

        void Update();
        void Draw();
};

inline void Player::BuffSpeed() { speed += 10; }
inline void Player::BuffBatteryTime() { battery->BuffBatteryBarTime(); }
inline void Player::BuffMiningSpeed() {
    miningSpeed -= 0.05f;
    if(miningSpeed <= maxMiningSpeed) miningSpeed = maxMiningSpeed;
}

inline Battery* Player::GetBattery() { return battery; }

inline bool Player::PlayerHasEscaped() { return playerHasEscaped; }
inline void Player::PlayerHasEscaped(bool hasEscaped) {
    playerHasEscaped = hasEscaped;
}

inline float Player::MiningSpeed() { return miningSpeed; }
inline float Player::SpriteSize() { return spriteSize; }
inline PLAYERSTATE Player::State() { return state; }

inline float Player::BatteryEnergy() { return battery->Energy(); }

inline int Player::HasBombs() { return bombsQuantity > 0; }
inline bool Player::RadarIsOnCooldown() { return radar->IsOnCooldown(); }

#endif