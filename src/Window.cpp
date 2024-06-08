//
// Created by mechlon on 06.06.24.
//

#include <iostream>

#include "Window.h"
#include "GlobalSettings.h"

Window::Window() {
    GlobalSettings& globalSettings = GlobalSettings::GetInstance();

    // Window init via SDL API
    if (auto error = SDL_Init(SDL_INIT_EVERYTHING)) {
        std::cout << "(SDL) Error when initalizing!" << std::endl;
    }

    if (auto error = SDL_CreateWindowAndRenderer(globalSettings.GetWindowWidth(),
                                                      globalSettings.GetWindowHeight(),
                                                      SDL_WINDOW_SHOWN,
                                                      &sdlWindowObject,
                                                      &sdlRenderer )) {
        std::cout << "(SDL) Error when trying to Create Window and/or Renderer" << std::endl;
    }
}

Window::~Window() {
    ClearRenderingVectors();
    SDL_DestroyRenderer(sdlRenderer);
    SDL_DestroyWindow(sdlWindowObject);
    SDL_Quit();
}

void Window::RenderAll() {
    SDL_SetRenderDrawColor(sdlRenderer, 0, 0, 0, 255);
    SDL_RenderClear(sdlRenderer);

    for(auto currentGameObject : visibleGameObjects){

        if(currentGameObject)
            currentGameObject->draw();
    }


}

void Window::ClearRenderingVectors() {
    visibleGameObjects.clear();
    // TBA possibly other visual classes, such as UI or backgrounds.
}

SDL_Renderer* Window::getRenderer() {
    return this->sdlRenderer;
}

SDL_Window* Window::getSdlWindow() {
    return this->sdlWindowObject;
}

