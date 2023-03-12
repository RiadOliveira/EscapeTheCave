#include "Engine.h"
#include "Home.h"
#include "Level2.h"
#include "Player.h"
#include <string>
#include <fstream>
using std::ifstream;
using std::string;

void Level2::Init() {
    scene = new Scene();

    Player * player = new Player();
    scene->Add(player, MOVING);
}

void Level2::Finalize() {
    delete backg;
    delete scene;
}

void Level2::Update() {
    if (window->KeyPress('B')) {
        viewBBox = !viewBBox;
    }

    if (window->KeyPress(VK_ESCAPE)) {
        Engine::Next<Home>();
    } else {
        scene->Update();
        scene->CollisionDetection();
    }
}

void Level2::Draw() {
    scene->Draw();
    if (viewBBox) scene->DrawBBox();
}
