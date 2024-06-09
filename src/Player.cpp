//
// Created by mechlon on 09.06.24.
//

#include "Player.h"
#include "Window.h"

Player::Player(Window* _window){
    window = _window;
    objectTexture = IMG_LoadTexture(window->renderer, "../data/ShipsPNG/ship0.png"); // Todo this and one below move to some Texture Management class
    SDL_QueryTexture(objectTexture, NULL, NULL, &textureWidth, &textureHeight);

}

void Player::Render(Window &window) {

//    SDL_Rect kwadrat = {renderPosX, renderPosY, 10, 10};
//    SDL_RenderFillRect(renderer, &kwadrat);

    SDL_Rect dstRect = { renderPosX, renderPosY, 32, 32 };
    SDL_Rect srcRect = { 0 , 0, 32, 32 };;
    SDL_RendererFlip flip;
    SDL_RenderCopyEx(window.renderer, objectTexture, &srcRect, &dstRect, angle, nullptr, flip);

}