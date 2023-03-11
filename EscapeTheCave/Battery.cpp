#include "Battery.h"

Battery::Battery(Player * player): player(player) {
    sprites = new Sprite*[spritesQuantity];
    string spritesPath = "Resources/Battery/Battery";

    for(int ind=0 ; ind<spritesQuantity ; ind++) {
        sprites[ind] = new Sprite(
            spritesPath + std::to_string(ind) + ".png"
        );
    }

    selectedSpriteIndex = spritesQuantity - 1;
    energyOfOneBatteryBar = player->MaxEnergy() / (spritesQuantity - 1);
    MoveTo(GetXPosition(), GetYPosition());
}

Battery::~Battery() {
    for(int ind=0 ; ind<spritesQuantity ; ind++) {
        delete sprites[ind];
    }

    delete[] sprites;
}

void Battery::OnCollision(Object * obj) {
}

void Battery::Update() {
    if(selectedSpriteIndex == 0) return;

    float energyToVerifyLoss = 
        energyOfOneBatteryBar * (spritesQuantity - selectedSpriteIndex);

    if(player->MaxEnergy() - player->Energy() >= energyToVerifyLoss) {
        selectedSpriteIndex--;
    } 
}

void Battery::Draw() {
    sprites[selectedSpriteIndex]->Draw(
        GetXPosition(), GetYPosition(), Layer::FRONT
    );
}
