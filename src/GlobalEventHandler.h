
#ifndef SPACE_PIRATES_GLOBALEVENTHANDLER_H
#define SPACE_PIRATES_GLOBALEVENTHANDLER_H

class GlobalEventHandler {
    // AKA fancy name (& java-esque solution) for the object to store game score
public:
    explicit GlobalEventHandler(int diffLevel);

    void RestartEventsHandler();

    bool gameOn = true;
    int gameOverTtl = 999;
    int score = 0;
    int difficulty;
};

#endif //SPACE_PIRATES_GLOBALEVENTHANDLER_H
