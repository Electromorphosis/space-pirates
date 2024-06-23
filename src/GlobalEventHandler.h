//
// Created by mechlon on 23.06.24.
//

#ifndef SPACE_PIRATES_GLOBALEVENTHANDLER_H
#define SPACE_PIRATES_GLOBALEVENTHANDLER_H

// AKA fancy name (& java-esque solution) for the object to store game score
class GlobalEventHandler {
public:
    int score = 0;
    int difficulty;
    bool gameOn = true;
    int gameOverTtl = 999;
    explicit GlobalEventHandler(int diffLevel);
    void RestartEventsHandler();
};


#endif //SPACE_PIRATES_GLOBALEVENTHANDLER_H
