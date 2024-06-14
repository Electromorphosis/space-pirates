//
// Created by mechlon on 09.06.24.
//

#ifndef SPACE_PIRATES_WINDOW_H
#define SPACE_PIRATES_WINDOW_H
#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <vector>
#include "GameObject.h"
#include <memory>

class GameObject;

class Window {
public:
    Window(int windowWidth, int windowHeight);
    int Width;
    int Height;
    ~Window();

    SDL_Window* window;
    SDL_Renderer* renderer;
    std::vector<std::unique_ptr<GameObject>> gameObjectsVector;
    std::unique_ptr<GameObject> player;

    void RenderAll();
};



#endif //SPACE_PIRATES_WINDOW_H