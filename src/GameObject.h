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
public:
    GameObject(VisibilityDelegate* visibilityDelegate, UpdateDelegate* updateDelegate);
    virtual ~GameObject();

    Window* window;

    void update();

    void draw(Window& sdlRenderer);

private:
    VisibilityDelegate* visibilityDelegate_;
    UpdateDelegate* updateDelegate_;
};



#endif //SPACE_PIRATES_OBJECT_H
