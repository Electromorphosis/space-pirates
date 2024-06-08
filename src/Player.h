//
// Created by mechlon on 06.06.24.
//

#ifndef SPACE_PIRATES_PLAYER_H
#define SPACE_PIRATES_PLAYER_H

#include "GameObject.h"
#include "VisibilityDelegate.h" // Assuming VisibilityDelegate is used
#include "UpdateDelegate.h"  // Assuming UpdateDelegate is used
#include "EventSystem.h"

class Player : public GameObject {
public:
    Player(Window* window, VisibilityDelegate* visibilityDelegate, UpdateDelegate* updateDelegate);

};

#endif // SPACE_PIRATES_PLAYER_H