#include "Engine.h"
#include "Home.h"
#include "Level2.h"
#include "Player.h"
#include "Pivot.h"
#include <string>
#include <fstream>
using std::ifstream;
using std::string;

void Level2::Init() {
    scene = new Scene();

    Player * player = new Player();
    scene->Add(player, MOVING);

    Pivot * pivot;
    bool left, right, up, down;
    float posX, posY;
    ifstream fin;

    fin.open("PivotsL2.txt");
    fin >> left;

    while (!fin.eof()) {
        if (fin.good()) {
            fin >> right; fin >> up; fin >> down; fin >> posX; fin >> posY;
            pivot = new Pivot(left, right, up, down);
            pivot->MoveTo(posX, posY);
            scene->Add(pivot, STATIC);
        } else {
            fin.clear();
            char temp[80];
            fin.getline(temp, 80);
        }
        
        fin >> left;
    }
    fin.close();
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
