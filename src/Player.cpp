//
// Created by mechlon on 06.06.24.
//

#include "Player.h"

Player::Player(Window* window, VisibilityDelegate* visibilityDelegate, UpdateDelegate* updateDelegate)
        : GameObject(visibilityDelegate, updateDelegate) {
    // Additional player specific initialization (if any)
}

int Player::getPlayerX() {
    return playerX;
}

int Player::getPlayerY() {
    return playerY;
}