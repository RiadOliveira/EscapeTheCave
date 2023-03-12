#include "Engine.h"
#include "Home.h"
#include "Level1.h"
#include "Level2.h"
#include "Player.h"
#include "Stone.h"
#include "MiningPoint.h"
#include "Battery.h"
#include "Pivot.h"

void Level1::CreateLevelStoneOrPivot(
    float positionX, float positionY
) {
    int xStartsWithoutStone = abs(window->CenterX() - positionX) < 64;
    int yStartsWithoutStone = abs(window->CenterY() - positionY) < 64;

    bool positionStartsWithoutStone = xStartsWithoutStone && yStartsWithoutStone;
    if(positionStartsWithoutStone) {
        Pivot * pivot = new Pivot();
        pivot->MoveTo(positionX, positionY);
        scene->Add(pivot, STATIC);
    } else {
        Stone * stone = new Stone(new Image*[2]{stoneImage, mossStoneImage}, 2);
        stone->MoveTo(positionX, positionY);
        scene->Add(stone, STATIC);
    }
}

void Level1::RenderLevelStonesAndPivots() {
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
            CreateLevelStoneOrPivot((float) xInd, (float) yInd);
        }
    }
}

void Level1::Init() {
    scene = new Scene();
    backg = new Sprite("Resources/LevelBackground.jpg");
    bombImage = new Image("Resources/Bomb/Bomb.png");

    Player * player = new Player(bombImage);
    scene->Add(player, MOVING);

    MiningPoint * miningPoint = new MiningPoint(player);
    scene->Add(miningPoint, MOVING);

    Battery * battery = new Battery(player);
    scene->Add(battery, STATIC);

    RenderLevelStonesAndPivots();
}

void Level1::Finalize() {
    delete backg;
    delete scene;
    delete stoneImage;
    delete mossStoneImage;
    delete bombImage;
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
