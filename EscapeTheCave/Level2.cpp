#include "Engine.h"
#include "Home.h"
#include "GameOver.h"
#include "Level2.h"
#include "Player.h"
#include "Stone.h"
#include "Pivot.h"
#include "MiningPoint.h"
#include "Bomb.h"
#include "random"

using std::mt19937;
using std::uniform_int_distribution;

int * Level2::GetEscapePoint() {
    mt19937 gen(rd());
    uniform_int_distribution<> dis(0, 1);

    bool isHorizontal = dis(gen);
    int stoneWidth = objectDefaultWidth;
    int halfStoneWidth = stoneWidth/2;

    if(isHorizontal) {
        bool isLeft = dis(gen);
        int xPosition = isLeft ?
            halfStoneWidth : window->Width() - halfStoneWidth;

        int verticalStonesAmount = window->Height() / stoneWidth;
        uniform_int_distribution<> yDis(0, verticalStonesAmount - 1);
        int generatedValue = yDis(gen);

        int yPosition = stoneWidth * generatedValue + stoneWidth;
        return new int[xPosition, yPosition];
    }
    
    bool isUp = dis(gen);
    int yPosition = isUp ?
        halfStoneWidth : window->Height() - halfStoneWidth;

    int horizontalStonesAmount = window->Width() / stoneWidth;
    uniform_int_distribution<> xDis(0, horizontalStonesAmount - 1);
    int generatedValue = xDis(gen);

    int xPosition = stoneWidth * generatedValue + stoneWidth;
    return new int[xPosition, yPosition];
}

bool Level2::HasCreatedPivot(float positionX, float positionY) {
    bool xStartsWithoutStone = abs(window->CenterX() - positionX) < 64;
    bool yStartsWithoutStone = abs(window->CenterY() - positionY) < 64;

    bool positionStartsWithoutStone = xStartsWithoutStone && yStartsWithoutStone;
    if(!positionStartsWithoutStone) return false;

    Pivot * pivot = new Pivot();
    pivot->MoveTo(positionX, positionY);
    scene->Add(pivot, STATIC);
    return true;
}

void Level2::CreateLevelStoneOrPivot(
    float positionX, float positionY,
    bool isEscapePoint
) {
    if(isEscapePoint) {
        Stone * stone = new Stone(2, new Stone(2));
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

void Level2::RenderLevelStonesAndPivots() {
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

void Level2::Init() {
    scene = new Scene();
    backg = new Sprite("Resources/LevelBackground.jpg");

    Battery * battery = new Battery();
    player = new Player(battery);

    scene->Add(player, MOVING);
    scene->Add(new MiningPoint(player), MOVING);
    scene->Add(battery, STATIC);
    
    RenderLevelStonesAndPivots();
}

void Level2::Finalize() {
    delete backg;
    delete scene;
}

void Level2::Update() {
    if (window->KeyPress('B')) viewBBox = !viewBBox;

    if(player->BatteryEnergy() == 0.0f) {
        Engine::Next<GameOver>();
    } else if (window->KeyPress(VK_ESCAPE)) {
        Engine::Next<Home>();
    } else if (window->KeyPress('N') || player->PlayerHasEscaped()) {
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
