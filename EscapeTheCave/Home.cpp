#include "Engine.h"
#include "Home.h"
#include "Help.h"
#include "GameLevel.h"
#include "GameOver.h"

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
    if (window->KeyPress('H')) Engine::Next<Help>();
    if (window->KeyPress('J')) Engine::Next<GameOver>();
}

void Home::Draw() {
    backg->Draw(window->CenterX(), window->CenterY(), Layer::BACK);
}
