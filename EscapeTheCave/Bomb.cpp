#include "Bomb.h"
#include "EscapeTheCave.h"
#include "Player.h"
#include "Stone.h"
#include "Image.h"
#include "GameLevel.h"

Image * Bomb::playedExplosionImage = nullptr;
Image ** Bomb::playedBombImages = nullptr;
Image * Bomb::generatedExplosionImage = nullptr;
Image ** Bomb::generatedBombImages = nullptr;

Bomb::Bomb(BOMBTYPE bombType):
    bombType(bombType), hasExploded(false), hasDecreasedPlayerEnergy(false),
    selectedSpriteState(INITIAL), previousElapsedTime(0.0f)
{
    SetBombsAndExplosionImages();

    float boxCoord = (float) playedBombImages[0]->Width()/2;
    BBox(new Rect(-boxCoord, -boxCoord, boxCoord, boxCoord));

    bool isPlayed = bombType == PLAYED;
    sprites = new Sprite*[3] {
        new Sprite(isPlayed ? playedBombImages[0] : generatedBombImages[0]),
        new Sprite(isPlayed ? playedBombImages[1] : generatedBombImages[1]),
        new Sprite(isPlayed ? playedExplosionImage : generatedExplosionImage)
    };

    timer = new Timer();
    type = BOMB;
}

void Bomb::SetBombsAndExplosionImages() {
    if(playedExplosionImage != nullptr) return;

    Image * playedBomb0 = new Image("Resources/Bomb/PlayedBomb0.png");
    Image * playedBomb1 = new Image("Resources/Bomb/PlayedBomb1.png");
    playedBombImages = new Image*[2]{ playedBomb0, playedBomb1 };

    Image * generatedBomb0 = new Image("Resources/Bomb/GeneratedBomb0.png");
    Image * generatedBomb1 = new Image("Resources/Bomb/GeneratedBomb1.png");
    generatedBombImages = new Image*[2]{ generatedBomb0, generatedBomb1 };

    playedExplosionImage = new Image("Resources/Bomb/PlayedExplosion.png");
    generatedExplosionImage = new Image("Resources/Bomb/GeneratedExplosion.png");
}

Bomb::~Bomb() {
    delete timer;

    for(int ind=0 ; ind<3 ; ind++) {
        delete sprites[ind];
    }
    delete [] sprites;    
}

void Bomb::OnCollision(Object * obj) {
    if(bombType == PLAYED) {
        if(obj->Type() == STONE) StoneCollision(obj);
        return;
    }

    if(obj->Type() == PLAYER) PlayerCollision(obj);
}

void Bomb::StoneCollision(Object * obj) {
    Stone * stone = (Stone *) obj;
    stone->Destroy();
}

void Bomb::PlayerCollision(Object * obj) {
    if(!hasExploded || hasDecreasedPlayerEnergy) return;

    Player * player = (Player *) obj;
    player->GetBattery()->DecreaseEnergyBar();
    player->GetBattery()->DecreaseEnergyBar();
    
    hasDecreasedPlayerEnergy = true;
}

void Bomb::Update() {
    if(timer->NotStarted()) {
        timer->Start();
        return;
    }

    float elapsed = timer->Elapsed();
    if(hasExploded) {
        if(elapsed >= 0.2f) GameLevel::GetScene()->Delete();
        return;
    }

    if(elapsed >= 2.0f) {
        BBox(new Circle(180.0f));
        selectedSpriteState = EXPLODED;

        hasExploded = true;
        timer->Reset();
        return;
    }

    if(elapsed >= previousElapsedTime + 0.3f) {
        previousElapsedTime = elapsed;
        selectedSpriteState = 
            selectedSpriteState == INITIAL ? EXPLODING : INITIAL;
    } 
}

void Bomb::Draw() {
    sprites[selectedSpriteState]->Draw(x, y, Layer::MIDDLE);
}
