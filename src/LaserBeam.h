//
// Created by mechlon on 15.06.24.
//

#ifndef SPACE_PIRATES_LASERBEAM_H
#define SPACE_PIRATES_LASERBEAM_H
#include "GameObject.h"
#include "CollisionBox.h"
#include "CollisionType.h"

class LaserBeam : public GameObject {
public:
    LaserBeam(Window* _window, float posX, float posY, int angle);
    ~LaserBeam();
    Window* window;
    int textureWidth = 9;
    int textureHeight = 9;

    void Render(Window &renderer) override;
    CollisionBox collisionBox = CollisionBox(nullptr, 0, 0, 0, 0, CollisionType::FriendlyProjectile);
    void updateCollisionBox();
    void CheckCollision(CollisionType ct);
    void Damage(int dp) override;
};


#endif //SPACE_PIRATES_LASERBEAM_H
