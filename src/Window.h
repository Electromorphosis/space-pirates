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

class GameObject;

class Window {
public:
    Window();
    ~Window();

    void RenderAll(); // Not sure for now if I would need additional singular render functionality.
SDL_Window getSdlWindow();
SDL_Renderer getRenderer();
    std::vector<GameObject*> getVisibleGameObjects();
    GlobalSettings getGlobalSettings();
private:
    SDL_Window *sdlWindowObject;
    SDL_Renderer *sdlRenderer;
    GlobalSettings *globalSettings_;
    std::vector<GameObject*> visibleGameObjects; // Tmp solution for moving POC - finally better solution imo is to have separate GameMapManager?
    const GlobalSettings& settings_ = GlobalSettings::GetInstance(); // Get the instance
};


#endif //SPACE_PIRATES_WINDOW_H
