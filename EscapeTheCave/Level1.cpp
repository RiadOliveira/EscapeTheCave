#include "Engine.h"
#include "Home.h"
#include "Level1.h"
#include "Level2.h"
#include "Player.h"
#include "Pivot.h"
#include "Stone.h"
#include <string>
#include <fstream>
using std::ifstream;
using std::string;

void Level1::Init() {
    scene = new Scene();
    backg = new Sprite("Resources/LevelBackground.jpg");
    stoneImage = new Image("Resources/Stone.jpg");

    Player * player = new Player();
    scene->Add(player, MOVING);

    Stone * stone;
    bool left, right, up, down;
    float posX, posY;

    ifstream fin;
    fin.open("PivotsL1.txt");
    fin >> left;

    while (!fin.eof()) {
        if (fin.good()) {
            fin >> right; fin >> up; fin >> down; fin >> posX; fin >> posY;
            
            stone = new Stone(stoneImage);
            stone->MoveTo(posX, posY);
            scene->Add(stone, STATIC);
        } else {
            fin.clear();
            char temp[80];
            fin.getline(temp, 80);
        }

        fin >> left;
    }

    fin.close();
}

void Level1::Finalize() {
    delete backg;
    delete scene;
    delete stoneImage;
}

void Level1::Update() {
    if (window->KeyPress('B')) {
        viewBBox = !viewBBox;
    }

    if (window->KeyPress(VK_ESCAPE)) {
        Engine::Next<Home>();
    } else if (window->KeyPress('N')) {
        Engine::Next<Level2>();
    } else {
        scene->Update();
        scene->CollisionDetection();
    }
}

void Level1::Draw() {
    backg->Draw(window->CenterX(), window->CenterY(), Layer::BACK);
    scene->Draw();

    if (viewBBox) scene->DrawBBox();
}
