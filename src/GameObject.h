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


class GameObject {
public:
    GameObject(VisibilityDelegate* visibilityDelegate, UpdateDelegate* updateDelegate);
    virtual ~GameObject();
//               ,CollisionDelegate* c
//            , _c(c)

    void update();

    void draw();

//    void collide(GameObject gameObject[]) {
//        _c->collide(gameObject);
//    }

private:
    VisibilityDelegate* visibilityDelegate_;
    UpdateDelegate* updateDelegate_;
};



#endif //SPACE_PIRATES_OBJECT_H
