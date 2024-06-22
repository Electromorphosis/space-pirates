//
// Created by mechlon on 15.06.24.
//

#ifndef SPACE_PIRATES_COLLISIONBOX_H
#define SPACE_PIRATES_COLLISIONBOX_H
#include "GameObject.h"
#include "CollisionType.h"

class CollisionBox : public GameObject {
public:
    CollisionBox(Window* _window, float posX, float posY, int width, int height, CollisionType ct);
    Window* window;
    void Render(Window &renderer) override;

    CollisionType boxCollisionType;
    int width;
    int height;

    void UpdatePosition(int newPosX, int newPosY);
    bool CheckCollision(const CollisionBox &otherBox);
//    std::string color = "default";
};


#endif //SPACE_PIRATES_COLLISIONBOX_H
