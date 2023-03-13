#include "Engine.h"
#include "Home.h"
#include "GameOver.h"
#include "Level1.h"
#include "Level2.h"
#include "Player.h"
#include "Stone.h"
#include "Pivot.h"
#include "MiningPoint.h"
#include "Bomb.h"
#include "EscapeLadder.h"
#include "random"

using std::mt19937;
using std::uniform_int_distribution;

int * Level1::GetEscapePoint() {
    mt19937 gen(rd());
    uniform_int_distribution<> dis(0, 1);

    bool isHorizontal = dis(gen);
    int stoneWidth = objectDefaultWidth;
    int halfStoneWidth = stoneWidth/2;

    int xPosition, yPosition;
    bool isUpOrLeft = dis(gen);

    if(isHorizontal) {
        xPosition = isUpOrLeft ?
            halfStoneWidth : window->Width() - halfStoneWidth;

        int verticalStonesAmount = window->Height() / stoneWidth;
        uniform_int_distribution<> yDis(0, verticalStonesAmount - 1);

        int generatedValue = yDis(gen);
        yPosition = stoneWidth * generatedValue + halfStoneWidth;
    } else {
        yPosition = isUpOrLeft ?
            halfStoneWidth : window->Height() - halfStoneWidth;

        int horizontalStonesAmount = window->Width() / stoneWidth;
        uniform_int_distribution<> xDis(0, horizontalStonesAmount - 1);

        int generatedValue = xDis(gen);
        xPosition = stoneWidth * generatedValue + halfStoneWidth;
    }
    
    return new int[2]{ xPosition, yPosition };
}

bool Level1::HasCreatedPivot(float positionX, float positionY) {
    bool xStartsWithoutStone = abs(window->CenterX() - positionX) < 64;
    bool yStartsWithoutStone = abs(window->CenterY() - positionY) < 64;

    bool positionStartsWithoutStone = xStartsWithoutStone && yStartsWithoutStone;
    if(!positionStartsWithoutStone) return false;

    Pivot * pivot = new Pivot();
    pivot->MoveTo(positionX, positionY);
    scene->Add(pivot, STATIC);
    return true;
}

void Level1::CreateLevelStoneOrPivot(
    float positionX, float positionY,
    bool isEscapePoint
) {
    if(isEscapePoint) {
        Stone * stone = new Stone(2, new EscapeLadder());
        stone->MoveTo(positionX, positionY);
        scene->Add(stone, STATIC);

        return;
    }
    if(HasCreatedPivot(positionX, positionY)) return;

    mt19937 gen(rd());
    uniform_int_distribution<> stoneTypeDis(0, 2);
    bool isBrokenStone = stoneTypeDis(gen) == 0;

    Stone * stone = new Stone(1 + !isBrokenStone);
    stone->MoveTo(positionX, positionY);
    scene->Add(stone, STATIC);
}

void Level1::RenderLevelStonesAndPivots() {
    int stoneWidth = objectDefaultWidth;
    int stoneHalfWidth = stoneWidth/2;

    int * escapePoint = GetEscapePoint();
    for(
        int xInd = stoneHalfWidth ;
        xInd <= window->Width() - stoneHalfWidth ;
        xInd += stoneWidth
    ) {
        for(
            int yInd = stoneHalfWidth ;
            yInd <= window->Height() - stoneHalfWidth ;
            yInd += stoneWidth
        ) {
            CreateLevelStoneOrPivot(
                (float) xInd, (float) yInd,
                xInd == escapePoint[0] && yInd == escapePoint[1]
            );
        }
    }
}

void Level1::Init() {
    scene = new Scene();
    backg = new Sprite("Resources/LevelBackground.jpg");

    Battery * battery = new Battery();
    player = new Player(battery);

    scene->Add(player, MOVING);
    scene->Add(new MiningPoint(player), MOVING);
    scene->Add(battery, STATIC);
    
    RenderLevelStonesAndPivots();
}

void Level1::Finalize() {
    delete backg;
    delete scene;
}

void Level1::Update() {
    if (window->KeyPress('B')) viewBBox = !viewBBox;

    if(player->BatteryEnergy() == 0.0f) {
        Engine::Next<GameOver>();
    } else if (window->KeyPress(VK_ESCAPE)) {
        Engine::Next<Home>();
    } else if (window->KeyPress('N') || player->PlayerHasEscaped()) {
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
