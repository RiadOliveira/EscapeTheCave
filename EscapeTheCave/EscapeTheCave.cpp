#include "Engine.h"
#include "Resources.h"
#include "Home.h"

int APIENTRY WinMain(
    _In_ HINSTANCE hInstance, 
    _In_opt_ HINSTANCE hPrevInstance, 
    _In_ LPSTR lpCmdLine, 
    _In_ int nCmdShow
) {
    Engine * engine = new Engine();

    engine->window->Mode(WINDOWED);
    engine->window->Size(960, 720);
    engine->window->Color(25, 25, 25);
    engine->window->Title("Escape The Cave");
    engine->window->Icon(IDI_ICON);

    engine->Start(new Home());
    delete engine;
}
