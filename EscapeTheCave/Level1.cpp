#include "Engine.h"
#include "Home.h"
#include "Level1.h"
#include "Level2.h"
#include "Player.h"
#include "Pivot.h"
#include "Stone.h"
#include "MiningPoint.h"
#include <cmath>
using std::ifstream;
using std::string;

void Level1::CreateLevelStone(
    int positionX, int positionY
) {
    int xStartsWithoutStone = abs(window->CenterX() - positionX) < 96;
    int yStartsWithoutStone = abs(window->CenterY() - positionY) < 96;

    bool positionStartsWithoutStone = xStartsWithoutStone && yStartsWithoutStone;
    if(positionStartsWithoutStone) return;

    Stone * stone = new Stone(stoneImage);
    stone->MoveTo(positionX, positionY);
    scene->Add(stone, STATIC);
}

void Level1::RenderLevelStones() {
    stoneImage = new Image("Resources/Stone.png");

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
            CreateLevelStone(xInd, yInd);
        }
    }
}

void Level1::Init() {
    scene = new Scene();
    backg = new Sprite("Resources/LevelBackground.jpg");

    Player * player = new Player();
    scene->Add(player, MOVING);

    MiningPoint * miningPoint = new MiningPoint(player);
    scene->Add(miningPoint, MOVING);

    RenderLevelStones();
}

void Level1::Finalize() {
    delete backg;
    delete scene;
    delete stoneImage;
}

void Level1::Update() {
    if (window->KeyPress('B')) {
        viewBBox = !viewBBox;
    }

    if (window->KeyPress(VK_ESCAPE)) {
        Engine::Next<Home>();
    } else if (window->KeyPress('N')) {
        Engine::Next<Level2>();
    } else {
        scene->Update();
        scene->CollisionDetection();
    }
}

void Level1::Draw() {
    backg->Draw(window->CenterX(), window->CenterY(), Layer::BACK);
    scene->Draw();

    if (viewBBox) scene->DrawBBox();
}
