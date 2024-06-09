//
// Created by mechlon on 08.06.24.
//

#include "GlobalSettings.h"
#include <SDL2/SDL.h>

GlobalSettings GlobalSettings::instance_; // Define the static instance

GlobalSettings& GlobalSettings::GetInstance() {
    return instance_;
}

int GlobalSettings::GetWindowHeight() {
    return WINDOW_HEIGHT;
}

int GlobalSettings::GetWindowWidth() {
    return WINDOW_WIDTH;
}

Uint32 GlobalSettings::GetFramerate() {
    return MS_PER_FRAME;
}
