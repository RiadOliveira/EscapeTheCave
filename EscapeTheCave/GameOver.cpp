#include "Engine.h"
#include "GameOver.h"
#include "GameLevel.h"
#include "Home.h"

void GameOver::Init() {
    backg = new Sprite("Resources/GameOverScreen.png");
    XKV8_4_Off = new Sprite("Resources/XKV8-4_Off.png");
}

void GameOver::Finalize() {
    delete backg;
    delete XKV8_4_Off;
}

void GameOver::Update() {
    if (window->KeyPress(VK_ESCAPE)) Engine::Next<Home>();
    if (window->KeyPress(VK_RETURN)) {
        level = 0;
        Engine::Next<GameLevel>();
    }
}

void GameOver::Draw() {
    backg->Draw(window->CenterX(), window->CenterY(), Layer::BACK);
    XKV8_4_Off->Draw(348.0f + (XKV8_4_Off->Width() / 2) + (100 * level), 260.0f + (XKV8_4_Off->Width() / 2), Layer::FRONT);
}
