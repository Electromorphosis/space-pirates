//
// Created by mechlon on 08.06.24.
//

#ifndef SPACE_PIRATES_EVENTSYSTEM_H
#define SPACE_PIRATES_EVENTSYSTEM_H

#include <SDL2/SDL.h>


class EventSystem {
public:
    static EventSystem& GetInstance();

    SDL_Event *sdlEventObjectRef;
private:
    static EventSystem instance_;
    ~EventSystem();

};


#endif //SPACE_PIRATES_EVENTSYSTEM_H
