#include "Sprite.h"
#include "Engine.h"

const float Layer::FRONT  = 0.00f;
const float Layer::UPPER  = 0.25f;
const float Layer::MIDDLE = 0.50f;
const float Layer::LOWER  = 0.75f;
const float Layer::BACK   = 0.99f;

Sprite::Sprite(string filename) {
    image = new Image(filename);
    localImage = true;
    
    sprite.width = image->Width();
    sprite.height = image->Height();
    sprite.texture = image->View();
}

Sprite::Sprite(const Image * img) {
    image = img;
    localImage = false;

    sprite.width = image->Width();
    sprite.height = image->Height();
    sprite.texture = image->View();
}


Sprite::~Sprite() {
    if (localImage) delete image;
}

void Sprite::Draw(float x, float y, float z) {
    sprite.x = x;
    sprite.y = y;
    sprite.depth = z;

    Engine::renderer->Draw(&sprite);
}
