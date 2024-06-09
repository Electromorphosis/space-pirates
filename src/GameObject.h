//
// Created by mechlon on 06.06.24.
//

#ifndef SPACE_PIRATES_OBJECT_H
#define SPACE_PIRATES_OBJECT_H

#include <string>

#include "Window.h"
#include "VisibilityDelegate.h"
#include "UpdateDelegate.h"
//#include "Collision.h"
class Window;

class GameObject {
    VisibilityDelegate* visibilityDelegate_;
    UpdateDelegate* updateDelegate_;
public:
    GameObject(VisibilityDelegate* visibilityDelegate, UpdateDelegate* updateDelegate)
    : visibilityDelegate_(visibilityDelegate)
    , updateDelegate_(updateDelegate)
    {}

    virtual ~GameObject();

    SDL_Texture* objectTexture = nullptr;
    void update();

    virtual void draw(Window& sdlRenderer);


    int x = 0;
    int y = 0;
};



#endif //SPACE_PIRATES_OBJECT_H
