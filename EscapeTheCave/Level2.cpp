#include "Engine.h"
#include "Home.h"
#include "Level2.h"
#include "Player.h"
#include "Stone.h"
#include "MiningPoint.h"
#include "Battery.h"

void Level2::CreateLevelStone(
    float positionX, float positionY
) {
    int xStartsWithoutStone = abs(window->CenterX() - positionX) < 96;
    int yStartsWithoutStone = abs(window->CenterY() - positionY) < 96;

    bool positionStartsWithoutStone = xStartsWithoutStone && yStartsWithoutStone;
    if(positionStartsWithoutStone) return;

    Stone * stone = new Stone(new Image*[2]{stoneImage, mossStoneImage}, 2);
    stone->MoveTo(positionX, positionY);
    scene->Add(stone, STATIC);
}

void Level2::RenderLevelStones() {
    stoneImage = new Image("Resources/Stone.png");
    mossStoneImage = new Image("Resources/MossStone.png");

    int windowWidth = window->Width();
    int windowHeight = window->Width();
    int stoneHalfWidth = stoneImage->Width()/2;
    int stoneHalfHeight = stoneImage->Height()/2;
    
    for(
        int xInd = stoneHalfWidth ;
        xInd <= windowWidth - stoneHalfWidth ;
        xInd += stoneImage->Width()
    ) {
        for(
            int yInd = stoneHalfHeight ;
            yInd <= windowHeight - stoneHalfHeight ;
            yInd += stoneImage->Height()
        ) {
            CreateLevelStone((float) xInd, (float) yInd);
        }
    }
}

void Level2::Init() {
    scene = new Scene();
    backg = new Sprite("Resources/LevelBackground.jpg");
    bombImage = new Image("Resources/Bomb.png");

    Player * player = new Player(bombImage);
    scene->Add(player, MOVING);

    MiningPoint * miningPoint = new MiningPoint(player);
    scene->Add(miningPoint, MOVING);

    Battery * battery = new Battery(player);
    scene->Add(battery, STATIC);

    RenderLevelStones();
}

void Level2::Finalize() {
    delete backg;
    delete scene;
    delete stoneImage;
    delete mossStoneImage;
    delete bombImage;
}

void Level2::Update() {
    if (window->KeyPress('B')) {
        viewBBox = !viewBBox;
    }

    if (window->KeyPress(VK_ESCAPE)) {
        Engine::Next<Home>();
    } else {
        scene->Update();
        scene->CollisionDetection();
    }
}

void Level2::Draw() {
    backg->Draw(window->CenterX(), window->CenterY(), Layer::BACK);
    scene->Draw();

    if (viewBBox) scene->DrawBBox();
}
