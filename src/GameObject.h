
#ifndef SPACE_PIRATES_GAMEOBJECT_H
#define SPACE_PIRATES_GAMEOBJECT_H

#include <string>

#include <SDL2/SDL_image.h>

#include "Window.h"
#include "GlobalEventHandler.h"

class Window;

class GameObject {
public:
    Window* window;
    GlobalEventHandler* geh;
    SDL_Texture* objectTexture = nullptr;
    int textureWidth = 0;
    int textureHeight = 0;
    float positionX;
    float positionY;
    int renderPosX;
    int renderPosY;
    virtual void Render(Window& renderer);
    virtual void Damage(int dp) = 0;
    int ttl;
    int angle;
    int hp;
    bool movable = false;
    int velocity = 0;
    std::string name = "None";
};


#endif //SPACE_PIRATES_GAMEOBJECT_H
