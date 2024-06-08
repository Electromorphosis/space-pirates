//
// Created by mechlon on 06.06.24.
//

#ifndef SPACE_PIRATES_PLAYER_H
#define SPACE_PIRATES_PLAYER_H

#include "GameObject.h"
#include "VisibilityDelegate.h" // Assuming VisibilityDelegate is used
#include "UpdateDelegate.h"  // Assuming UpdateDelegate is used

class Player : public GameObject {
public:
    Player(Window* window, VisibilityDelegate* visibilityDelegate, UpdateDelegate* updateDelegate);

    // Additional player specific functions and member variables
    int getPlayerX();
    int getPlayerY();

private:
    int playerX = 0;
    int playerY = 0;
};

#endif // SPACE_PIRATES_PLAYER_H