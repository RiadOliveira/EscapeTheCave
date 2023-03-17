#include "Battery.h"
#include "Engine.h"

const float Battery::maxEnergy = 100.0f;

Battery::Battery(): energy(maxEnergy), timeOfOneBatteryBar(4.0f) {
    sprites = new Sprite*[spritesQuantity];
    string spritesPath = "Resources/Battery/Battery";

    for(int ind=0 ; ind<spritesQuantity ; ind++) {
        sprites[ind] = new Sprite(
            spritesPath + std::to_string(ind) + ".png"
        );
    }

    selectedSpriteIndex = spritesQuantity - 1;
    energyOfOneBatteryBar = maxEnergy / (spritesQuantity - 1);
    MoveTo(GetXPosition(), GetYPosition());

    timer = new Timer();
    timer->Start();
}

void Battery::ResetDataToNewLevel() {
    energy = maxEnergy;
    selectedSpriteIndex = spritesQuantity - 1;
    timer->Reset();
}

Battery::~Battery() {
    delete timer;
    
    for(int ind=0 ; ind<spritesQuantity ; ind++) {
        delete sprites[ind];
    }
    delete[] sprites;
}

void Battery::OnCollision(Object * obj) {
}

void Battery::Update() {
    if(selectedSpriteIndex == 0) {
        if(timer->Elapsed() >= timeOfOneBatteryBar/2) energy = 0.0f;
        return;
    }
    if(timer->Elapsed() < timeOfOneBatteryBar) return;

    DecreaseEnergyBar();
    timer->Reset();
}

void Battery::Draw() {
    sprites[selectedSpriteIndex]->Draw(
        GetXPosition(), GetYPosition(), Layer::FRONT
    );
}
