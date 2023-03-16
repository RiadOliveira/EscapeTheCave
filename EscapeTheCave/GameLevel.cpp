#include "Engine.h"
#include "Home.h"
#include "GameOver.h"
#include "GameLevel.h"
#include "Player.h"
#include "Stone.h"
#include "Pivot.h"
#include "MiningPoint.h"
#include "Bomb.h"
#include "Generator.h"
#include "random"

using std::mt19937;
using std::uniform_int_distribution;

uint      GameLevel::level    = 0;
Player*   GameLevel::player   = nullptr;
Scene*    GameLevel::scene    = nullptr;

int * GameLevel::GetEscapePoint() {
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

bool GameLevel::HasCreatedPivot(float positionX, float positionY) {
    bool xStartsWithoutStone = abs(window->CenterX() - positionX) < 64;
    bool yStartsWithoutStone = abs(window->CenterY() - positionY) < 64;

    bool positionStartsWithoutStone = xStartsWithoutStone && yStartsWithoutStone;
    if(!positionStartsWithoutStone) return false;

    Pivot * pivot = new Pivot();
    pivot->MoveTo(positionX, positionY);
    scene->Add(pivot, STATIC);
    return true;
}

void GameLevel::CreateLevelStoneOrPivot(
    float positionX, float positionY,
    bool isEscapePoint
) {
    if(isEscapePoint) {
        Stone * stone = new Stone(level + 2, new Generator());
        stone->MoveTo(positionX, positionY);
        scene->Add(stone, STATIC);

        return;
    }
    if(HasCreatedPivot(positionX, positionY)) return;

    mt19937 gen(rd());
    uniform_int_distribution<> stoneTypeDis(0, 2);
    bool isBrokenStone = stoneTypeDis(gen) == 0;

    Stone * stone = new Stone(level + 1 + !isBrokenStone);
    stone->MoveTo(positionX, positionY);
    scene->Add(stone, STATIC);
}

void GameLevel::RenderLevelStonesAndPivots() {
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

void GameLevel::Init() {
    scene = new Scene();
    backg = new Sprite("Resources/LevelBackground.jpg");

    if(player == nullptr) {
        Battery * battery = new Battery();
        player = new Player(battery);
    } else player->ResetDataToNewLevel();

    scene->Add(player, MOVING);
    scene->Add(new MiningPoint(player), MOVING);
    scene->Add(player->GetBattery(), STATIC);
    
    RenderLevelStonesAndPivots();
}

void GameLevel::Finalize() {
    level++;

    delete backg;
    scene->Remove(player, MOVING);
    scene->Remove(player->GetBattery(), STATIC);
    delete scene;
}

void GameLevel::Update() {
    if (window->KeyPress('B')) viewBBox = !viewBBox;

    if(player->BatteryEnergy() <= 0.0f) {
        scene->Delete(player->GetBattery(), STATIC);
        scene->Delete(player, MOVING);

        Engine::Next<GameOver>();
    } else if (window->KeyPress(VK_ESCAPE)) {
        scene->Delete(player->GetBattery(), STATIC);
        scene->Delete(player, MOVING);
        
        Engine::Next<Home>();
    } else if (window->KeyPress('N') || player->PlayerHasEscaped()) {
        Engine::Next<GameLevel>();
    } else {
        scene->Update();
        scene->CollisionDetection();
    }
}

void GameLevel::Draw() {
    backg->Draw(window->CenterX(), window->CenterY(), Layer::BACK);
    scene->Draw();

    if (viewBBox) scene->DrawBBox();
}
