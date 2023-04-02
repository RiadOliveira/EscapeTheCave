#include "Engine.h"
#include "Victory.h"
#include "GameLevel.h"
#include "Home.h"

void Victory::Init() {
    backg = new Sprite("Resources/VictoryScreen.png");
}

void Victory::Finalize() {
    delete backg;
}

void Victory::Update() {
    if (window->KeyPress(VK_ESCAPE)) Engine::Next<Home>();
    if (window->KeyPress(VK_RETURN)) {
        level = 0;
        Engine::Next<GameLevel>();
    }
}

void Victory::Draw() {
    backg->Draw(window->CenterX(), window->CenterY(), Layer::BACK);
}
