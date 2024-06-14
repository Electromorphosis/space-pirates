//
// Created by mechlon on 09.06.24.
//

#ifndef SPACE_PIRATES_ROCK_H
#define SPACE_PIRATES_ROCK_H
#include "GameObject.h"
#include <string>

class Rock : public GameObject {
public:
    Rock(Window* _window);
    Rock(Window* _window, std::string spawn);
    Window* window;
    int textureWidth = 32;
    int textureHeight = 32;
    float positionX = 0;
    float positionY = 0;
    int angle = 0;

    void Render(Window &renderer) override;
};


#endif //SPACE_PIRATES_ROCK_H
