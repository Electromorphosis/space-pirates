//
// Created by mechlon on 09.06.24.
//

#ifndef SPACE_PIRATES_GAMEOBJECT_H
#define SPACE_PIRATES_GAMEOBJECT_H
#include "Window.h"
#include <SDL2/SDL_image.h>
#include <string>
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
    virtual void Damage();
    int ttl;
    int angle;
    int hp;
    bool movable = false;
    int velocity = 0;
    std::string name = "None";
};


#endif //SPACE_PIRATES_GAMEOBJECT_H
