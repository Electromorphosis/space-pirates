
#ifndef SPACE_PIRATES_GAMEOBJECT_H
#define SPACE_PIRATES_GAMEOBJECT_H

#include <string>

#include <SDL2/SDL_image.h>

#include "Window.h"
#include "GlobalEventHandler.h"

class Window;

class GameObject {
public:
    virtual void Render(Window& renderer);
    virtual void Damage(int dp) = 0;

    SDL_Texture* objectTexture = nullptr;
    std::string name = "None";
    Window* window;
    GlobalEventHandler* geh;

    bool movable = false;
    int textureWidth = 0;
    int textureHeight = 0;
    int velocity = 0;
    float positionX;
    float positionY;
    int renderPosX;
    int renderPosY;
    int ttl;
    int angle;
    int hp;
};


#endif //SPACE_PIRATES_GAMEOBJECT_H
