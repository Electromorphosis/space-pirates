
#ifndef SPACE_PIRATES_PLAYER_H
#define SPACE_PIRATES_PLAYER_H

#include "GameObject.h"

class Player : public GameObject {
public:
    enum PlayerAnimationStates {
        IDLE,
        FORWARD,
        BACKWARDS,
        CLOCKWISE_TURN,
        COUNTER_TURN,
        SHOOT,
        DAMAGED,
        DESTROY
    };

    Player(Window* _window);
    void Render(Window &renderer) override;
    void UpdateAnimState(Window &renderer);
    void Damage(int dp) override;

    PlayerAnimationStates currentAnimationState = IDLE;

    bool damaged = true;
    bool isShooting = false;
    int textureWidth = 32;
    int textureHeight = 32;
    float positionX = 0;
    float positionY = 0;
    float velocity = 0;
    int angle = 0;
    int frameCounter = 0;
    int animStateTtl = 0;
};

#endif //SPACE_PIRATES_PLAYER_H
