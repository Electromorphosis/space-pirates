//
// Created by mechlon on 06.06.24.
//

#ifndef SPACE_PIRATES_PLAYER_H
#define SPACE_PIRATES_PLAYER_H

#include "GameObject.h"
#include "VisibilityDelegate.h" // Assuming VisibilityDelegate is used
#include "UpdateDelegate.h"  // Assuming UpdateDelegate is used
#include "EventSystem.h"

class Player : public GameObject {
public:
    Player(SDL_Renderer* sdlRenderer, TextureData* textureData)
    : GameObject(new Visible(sdlRenderer, textureData), new Movable()) {
        objectTexture = IMG_LoadTexture(sdlRenderer, "../data/ShipsPNG/ship0.png");
        SDL_QueryTexture(objectTexture, NULL, NULL, new int(32), new int(32)); // Todo - don't do it like that, memory leak will occur

    };

    void draw(Window& window) override;


};

#endif // SPACE_PIRATES_PLAYER_H