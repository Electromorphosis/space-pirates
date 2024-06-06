//
// Created by mechlon on 06.06.24.
//

#ifndef SPACE_PIRATES_PLAYER_H
#define SPACE_PIRATES_PLAYER_H

#include "GameObject.h"
#include "Window.h"

class Player : public GameObject {
public:
    Player(Window*  *_window)
            : GameObject(
            new Visible(),
            new Movable(),
            new Solid()) {};

    ~Player();

    float positionX = 100;
    float positionY = 100;
    float velocityX;
    float velocityY;
};

#endif //SPACE_PIRATES_PLAYER_H
