#include "Radar.h"
#include "Engine.h"
#include "GameLevel.h"

Radar::Radar():
    radarDirection(DISABLED), previousElapsedTime(0.0f),
    showingRadar(true) 
{
    sprites = new Sprite*[spritesQuantity];
    string spritesPath = "Resources/Radar";

    sprites[RADAR_UP] = new Sprite(spritesPath + "/RadarUp.png");
    sprites[RADAR_DOWN] = new Sprite(spritesPath + "/RadarDown.png");
    sprites[RADAR_LEFT] = new Sprite(spritesPath + "/RadarLeft.png");
    sprites[RADAR_RIGHT] = new Sprite(spritesPath + "/RadarRight.png");

    timer = new Timer();
}

Radar::~Radar() {
    delete timer;
    
    for(int ind=0 ; ind<spritesQuantity ; ind++) {
        delete sprites[ind];
    }
    delete[] sprites;
}

void Radar::ActivateRadar() {
    if(!timer->NotStarted() && timer->Elapsed() <= 3.0f) return;

    Player * player = GameLevel::GetPlayer();
    player->GetBattery()->DecreaseEnergyBar();

    int * &escapePoint = GameLevel::GetEscapePoint();
    float xDifference = escapePoint[0] - player->X();
    float yDifference = escapePoint[1] - player->Y();

    bool radarWillBeHorizontally = abs(yDifference) < abs(xDifference);
    if(radarWillBeHorizontally) {
        radarDirection = xDifference > 0 ? RADAR_RIGHT : RADAR_LEFT;
    } else {
        radarDirection = yDifference > 0 ? RADAR_DOWN : RADAR_UP;
    }

    previousElapsedTime = 0.0f;
    showingRadar = true;
    timer->Reset();
}

void Radar::ResetDataToNewLevel() {
    radarDirection = DISABLED;
}

void Radar::OnCollision(Object * obj) {
}

void Radar::Update() {
    if(radarDirection == DISABLED) return;

    float elapsed = timer->Elapsed();
    if(elapsed >= 3.0f) {
        radarDirection = DISABLED;
        return;
    }

    float elapsedDifference = showingRadar ? 0.5f : 0.3f;
    if (elapsed >= previousElapsedTime + elapsedDifference) {
        previousElapsedTime = elapsed;
        showingRadar = !showingRadar;
    }
}

void Radar::Draw() {
    if(radarDirection == DISABLED) return;
    Player * player = GameLevel::GetPlayer();

    float positionX, positionY;
    float distanceFromPlayer = player->SpriteSize()/2 + 32.0f;

    if(radarDirection == RADAR_UP || radarDirection == RADAR_DOWN) {
        positionX = player->X();
        positionY = player->Y() +
            (radarDirection == RADAR_UP ? -distanceFromPlayer : distanceFromPlayer);
    } else {
        positionY = player->Y();
        positionX = player->X() +
            (radarDirection == RADAR_LEFT ? -distanceFromPlayer : distanceFromPlayer);
    }

    if(showingRadar) {
        sprites[radarDirection]->Draw(positionX, positionY, Layer::FRONT);
    }
}
