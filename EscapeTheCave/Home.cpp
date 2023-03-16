#include "Engine.h"
#include "Home.h"
#include "GameLevel.h"

void Home::Init() {
    backg = new Sprite("Resources/TitleScreen.png");
    level = 0;
}

void Home::Finalize() {
    delete backg;
}

void Home::Update() {
    if (window->KeyPress(VK_ESCAPE)) window->Close();
    if (window->KeyPress(VK_RETURN)) Engine::Next<GameLevel>();
}

void Home::Draw() {
    backg->Draw(window->CenterX(), window->CenterY(), Layer::BACK);
}
