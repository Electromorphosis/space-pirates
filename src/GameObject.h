//
// Created by mechlon on 06.06.24.
//

#ifndef SPACE_PIRATES_OBJECT_H
#define SPACE_PIRATES_OBJECT_H

#include <string>

#include "Window.h"
#include "Visibility.h"
#include "Update.h"
#include "Collision.h"


class GameObject
{
    Window* window;
    VisibilityDelegate* _v;
    UpdateDelegate* _u;
    CollisionDelegate* _c;

    float positionX;
    float positionY;

public:
    virtual GameObject(VisibilityDelegate* v, UpdateDelegate* u, CollisionDelegate* c)
            : _v(v)
            , _u(u)
            , _c(c)
    {}

    void update() {
        _u->update();
    }

    void draw() {
        _v->draw();
    }

    void collide(GameObject gameObject[]) {
        _c->collide(gameObject);
    }
};



#endif //SPACE_PIRATES_OBJECT_H
