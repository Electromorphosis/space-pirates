
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

    void UpdatePosition(float newPosX, float newPosY);
//    std::string color = "default";
void Damage(int dp) override;
};


#endif //SPACE_PIRATES_COLLISIONBOX_H
