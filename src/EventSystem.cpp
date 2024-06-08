//
// Created by mechlon on 08.06.24.
//

#include "EventSystem.h"

EventSystem EventSystem::instance_; // Define the static instance

EventSystem& EventSystem::GetInstance() {
    return instance_;
}

EventSystem::~EventSystem() {

}
