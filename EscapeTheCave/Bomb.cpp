#include "Bomb.h"
#include "EscapeTheCave.h"
#include "Player.h"
#include "Stone.h"
#include "Image.h"

Image * Bomb::explosionImage = nullptr;
Image ** Bomb::bombImages = nullptr;

Bomb::Bomb(BOMBTYPE bombType):
    bombType(bombType), hasExploded(false),
    selectedSpriteState(INITIAL), previousElapsedTime(0.0f)
{
    if(bombImages == nullptr) {
        Image * initialBomb = new Image("Resources/Bomb/BombInitial.png");
        Image * explodingBomb = new Image("Resources/Bomb/BombExploding.png");

        bombImages = new Image*[2]{ initialBomb, explodingBomb };
    }

    if(explosionImage == nullptr) {
        explosionImage = new Image("Resources/Bomb/Explosion.png");
    }

    timer = new Timer();
    BBox(new Rect(-32, -32, 32, 32));
    sprites = new Sprite*[3] {
        new Sprite(bombImages[0]),
        new Sprite(bombImages[1]),
        new Sprite(explosionImage)
    };

    type = BOMB;
}

Bomb::~Bomb() {
    delete timer;

    for(int ind=0 ; ind<3 ; ind++) {
        delete sprites[ind];
    }
    delete [] sprites;    
}

void Bomb::OnCollision(Object * obj) {
    if(obj->Type() == STONE && bombType == PLAYED) StoneCollision(obj);
    else if(obj->Type() == PLAYER && bombType == GENERATED) PlayerCollision(obj);
}

void Bomb::StoneCollision(Object * obj) {
    Stone * stone = (Stone *) obj;
    stone->Destroy();
}

void Bomb::PlayerCollision(Object * obj) {
    Player * player = (Player *) obj;
}

void Bomb::Update() {
    if(timer->NotStarted()) {
        timer->Start();
        return;
    }

    float elapsed = timer->Elapsed();
    if(hasExploded) {
        if(elapsed >= 0.2) Game::GetScene()->Delete();
        return;
    }

    if(elapsed >= 3.0f) {
        BBox(new Circle(90.0f));
        selectedSpriteState = EXPLODED;

        hasExploded = true;
        timer->Reset();
        return;
    }

    if(elapsed >= previousElapsedTime + 0.3) {
        previousElapsedTime = elapsed;
        selectedSpriteState = 
            selectedSpriteState == INITIAL ? EXPLODING : INITIAL;
    } 
}

void Bomb::Draw() {
    sprites[selectedSpriteState]->Draw(x, y, Layer::UPPER);
}
