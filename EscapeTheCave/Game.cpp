#include "Game.h"
#include "Engine.h"
#include "Scene.h"

uint      Game::level    = 0;
Window* & Game::window   = Engine::window;
float   & Game::gameTime = Engine::frameTime;

Game::Game() {
}

Game::~Game() {
}

void Game::OnPause() {
    Sleep(10);
}
