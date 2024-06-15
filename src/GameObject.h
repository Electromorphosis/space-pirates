//
// Created by mechlon on 09.06.24.
//

#ifndef SPACE_PIRATES_GAMEOBJECT_H
#define SPACE_PIRATES_GAMEOBJECT_H
#include "Window.h"
#include <SDL2/SDL_image.h>
class Window;

class GameObject {
public:
    Window* window;
    SDL_Texture* objectTexture = nullptr;
    int textureWidth;
    int textureHeight;
    float positionX;
    float positionY;
    int renderPosX;
    int renderPosY;
    virtual void Render(Window& renderer) = 0;
    int ttl;
    int angle;
};


#endif //SPACE_PIRATES_GAMEOBJECT_H
