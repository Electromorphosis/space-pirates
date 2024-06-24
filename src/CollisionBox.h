
#ifndef SPACE_PIRATES_COLLISIONBOX_H
#define SPACE_PIRATES_COLLISIONBOX_H

#include "GameObject.h"
#include "CollisionType.h"

class CollisionBox : public GameObject {
public:
    CollisionBox(Window* _window, float posX, float posY, int width, int height, CollisionType ct);

    void Render(Window &renderer) override;
    void UpdatePosition(float newPosX, float newPosY);
    void Damage(int dp) override;

    Window* window;
    CollisionType boxCollisionType;

    int width;
    int height;
};

#endif //SPACE_PIRATES_COLLISIONBOX_H
