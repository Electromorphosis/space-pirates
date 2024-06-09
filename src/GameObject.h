//
// Created by mechlon on 09.06.24.
//

#ifndef SPACE_PIRATES_GAMEOBJECT_H
#define SPACE_PIRATES_GAMEOBJECT_H
#include <SDL2/SDL_image.h>

class GameObject {
public:

    SDL_Texture* objectTexture = nullptr;
    int textureWidth;
    int textureHeight;
    float positionX;
    float positionY;
};


#endif //SPACE_PIRATES_GAMEOBJECT_H
