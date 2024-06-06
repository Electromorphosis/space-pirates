//
// Created by mechlon on 06.06.24.
//

#include "Player.h"
#include "Window.h"

Player(Window *_window) {
    _window->globalGameObjects.push_back(static_cast<Object*>(this));
}