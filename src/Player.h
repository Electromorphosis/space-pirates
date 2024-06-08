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

private:
    // No private member variables needed in this example (assuming everything is inherited)
};

#endif // SPACE_PIRATES_PLAYER_H