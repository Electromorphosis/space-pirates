//
// Created by mechlon on 09.06.24.
//

#ifndef SPACE_PIRATES_PLAYER_H
#define SPACE_PIRATES_PLAYER_H
#include "GameObject.h"

class Player : public GameObject {
public:
    Player(Window* _window);

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
    PlayerAnimationStates currentAnimationState = IDLE;
    int textureWidth = 32;
    int textureHeight = 32;
    float positionX = 0;
    float positionY = 0;
    float velocity = 0;
    int angle = 0;
    int frameCounter = 0;
    bool isShooting = false;
    void Render(Window &renderer) override;
    void UpdateAnimState(Window &renderer);
    void Damage(int dp) override;
    int animStateTtl = 0;
    bool damaged = true;
};


#endif //SPACE_PIRATES_PLAYER_H
