/**********************************************************************************
// Object (C�digo Fonte)
//
// Cria��o:     01 Out 2007
// Atualiza��o: 28 Fev 2023
// Compilador:  Visual C++ 2022
//
// Descri��o:   Essa � a classe base para todos objetos do jogo.
//
//              Um objeto do jogo � qualquer coisa que poss�mos querer desenhar
//              ou interagir dentro do jogo. Por exemplo, um soldado, um pr�dio,
//              um proj�til, uma forma geom�trica, etc.
//
**********************************************************************************/

#include "Object.h"
#include "Engine.h"

// -------------------------------------------------------------------------------
// Inicializa��o de vari�veis est�ticas da classe

Window* & Object::window   = Engine::window;        // ponteiro para a janela
Game*   & Object::game     = Engine::game;          // ponteiro para o jogo
float   & Object::gameTime = Engine::frameTime;     // tempo do �ltimo quadro

// -------------------------------------------------------------------------------

Object::Object()
{
    // posi��o do objeto
    posX = posY = 0.0f;

    // profundidade do objeto
    posZ = 0.5f;

    //tipo do objeto
    type = 0;

    // bounding box do objeto
    bbox = nullptr;
}

// -------------------------------------------------------------------------------

Object::~Object()
{
    if (bbox)
        delete bbox;
}

// -------------------------------------------------------------------------------

void Object::BBox(Geometry* bb)
{
    if (bbox)
        delete bbox;

    bbox = bb;
    bbox->MoveTo(x, y);
}

// -------------------------------------------------------------------------------

void Object::Translate(float dx, float dy, float dz)
{
    posX += dx;
    posY += dy;
    posZ += dz;

    if (bbox)
        bbox->Translate(dx, dy);
}

// -------------------------------------------------------------------------------

void Object::MoveTo(float px, float py, float pz)
{
    posX = px;
    posY = py;
    posZ = pz;

    if (bbox)
        bbox->MoveTo(px, py);
}

// -------------------------------------------------------------------------------

void Object::MoveTo(float px, float py)
{
    posX = px;
    posY = py;

    if (bbox)
        bbox->MoveTo(px, py);
}

// -------------------------------------------------------------------------------

void Object::OnCollision(Object* obj)
{
}

// -------------------------------------------------------------------------------