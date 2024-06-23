//
// Created by mechlon on 23.06.24.
//

#include "GlobalEventHandler.h"

GlobalEventHandler::GlobalEventHandler(int diffLevel) {
    difficulty = diffLevel;

}

void GlobalEventHandler::RestartEventsHandler() {
    score = 0;
    gameOn = false;
    gameOverTtl = 999;

}
