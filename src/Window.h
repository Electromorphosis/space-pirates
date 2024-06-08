//
// Created by mechlon on 06.06.24.
//

#ifndef SPACE_PIRATES_WINDOW_H
#define SPACE_PIRATES_WINDOW_H

#include <vector>
#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>

#include "GlobalSettings.h"
#include "GameObject.h"

class Window {
public:
    SDL_Window *sdl_window_obj;
    SDL_Renderer *renderer;

    GlobalSettings* _GS;

    int windowWidth = _GS->WINDOW_WIDTH;
    int windowHeight = _GS->WINDOW_HEIGHT;

    Window();
    ~Window();

//    std::vector<GameObject*> globalGameObjects; // Tmp solution for moving POC - finally better solution imo is to have separate GameMapManager?

//    void Render(std::vector<GameObject*> objToRender);
    void RenderAll();
    void DeInitial(); // Not sure if it would be needed really
};


#endif //SPACE_PIRATES_WINDOW_H
