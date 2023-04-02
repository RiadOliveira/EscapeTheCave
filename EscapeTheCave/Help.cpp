#include "Engine.h"
#include "Help.h"
#include "Home.h"
#include "GameLevel.h"


void Help::Init() {
    backg = new Sprite("Resources/HelpScreen.png");
    level = 0;
}

void Help::Finalize() {
    delete backg;
}

void Help::Update() {
    if (window->KeyPress(VK_ESCAPE)) Engine::Next<Home>();
    if (window->KeyPress(VK_RETURN)) Engine::Next<GameLevel>();
}

void Help::Draw() {
    backg->Draw(window->CenterX(), window->CenterY(), Layer::BACK);
}
