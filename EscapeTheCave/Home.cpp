#include "Engine.h"
#include "Home.h"
#include "Level1.h"

void Home::Init() {
    backg = new Sprite("Resources/TitleScreen.png");
}

void Home::Finalize() {
    delete backg;
}

void Home::Update() {
    if (window->KeyPress(VK_ESCAPE)) window->Close();
    if (window->KeyPress(VK_RETURN)) Engine::Next<Level1>();
}

void Home::Draw() {
    backg->Draw(window->CenterX(), window->CenterY(), Layer::BACK);
}
