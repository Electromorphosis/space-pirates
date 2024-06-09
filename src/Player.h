//
// Created by mechlon on 09.06.24.
//

#ifndef SPACE_PIRATES_PLAYER_H
#define SPACE_PIRATES_PLAYER_H
#include "GameObject.h"

class Player : public GameObject {
public:
    Player();
    int textureWidth = 32;
    int textureHeight = 32;
    float positionX = 0;
    float positionY = 0;
    float velocity = 0;
    int angle = 0;
};


#endif //SPACE_PIRATES_PLAYER_H
