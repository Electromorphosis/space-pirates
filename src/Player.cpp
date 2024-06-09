//
// Created by mechlon on 06.06.24.
//

#include "Player.h"

void Player::draw(Window &window) {
    GameObject::draw(window);


    SDL_Rect dstRect = { x, static_cast<int>(y), 32, 32 };
    SDL_Rect srcRect = { 0 , 0, 32, 32 };;





    SDL_RendererFlip flip;
    SDL_RenderCopyEx(window.getRenderer(), objectTexture, &srcRect, &dstRect,0.0f, NULL, flip);
}
