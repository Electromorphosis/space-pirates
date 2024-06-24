
#include "GlobalEventHandler.h"

GlobalEventHandler::GlobalEventHandler(int diffLevel) {
    difficulty = diffLevel;

}

void GlobalEventHandler::RestartEventsHandler() {
    score = 0;
    gameOn = false;
    gameOverTtl = 999;

}
