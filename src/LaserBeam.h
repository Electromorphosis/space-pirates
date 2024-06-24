
#ifndef SPACE_PIRATES_LASERBEAM_H
#define SPACE_PIRATES_LASERBEAM_H

#include "GameObject.h"
#include "CollisionBox.h"
#include "CollisionType.h"

class LaserBeam : public GameObject {
    // LaserBeam == Friendly, player's laser - at least for now.
public:
    LaserBeam(Window* _window, float posX, float posY, int angle);
    ~LaserBeam();

    void Render(Window &renderer) override;
    void Damage(int dp) override;
    void CheckCollision(CollisionType ct);
    void updateCollisionBox();

    CollisionBox collisionBox = CollisionBox(nullptr, 0, 0, 0, 0, CollisionType::FriendlyProjectile);
    Window* window;

    int textureWidth = 9;
    int textureHeight = 9;
};

#endif //SPACE_PIRATES_LASERBEAM_H
