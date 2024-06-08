//
// Created by mechlon on 06.06.24.
//

#include "GameObject.h"

GameObject::GameObject(VisibilityDelegate* visibilityDelegate, UpdateDelegate* updateDelegate)
        : visibilityDelegate_(visibilityDelegate), updateDelegate_(updateDelegate) {}

GameObject::~GameObject() {
    // Destructor implementation (if needed for derived classes with dynamically allocated delegates)
    // delete visibilityDelegate_;
    // delete updateDelegate_;
}

void GameObject::update() {
    updateDelegate_->update();
}

void GameObject::draw(Window& sdlRenderer) {
    visibilityDelegate_->draw();
}