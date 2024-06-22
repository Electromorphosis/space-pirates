//
// Created by mechlon on 09.06.24.
//

#include "Player.h"
#include "Window.h"

Player::Player(Window* _window){
    window = _window;
    positionX = static_cast<float>(window->Width)/2;
    renderPosX = static_cast<int>(positionX);
    positionY = static_cast<float>(window->Height)/2;
    renderPosY = static_cast<int>(positionY);
    objectTexture = IMG_LoadTexture(window->renderer, "../data/ShipsPNG/ship0.png"); // Todo this and one below move to some Texture Management class
    SDL_QueryTexture(objectTexture, NULL, NULL, &textureWidth, &textureHeight);

}

void Player::Render(Window &window) {
    switch (currentAnimationState) {
        case IDLE:
            objectTexture = IMG_LoadTexture(window.renderer, "../data/ShipsPNG/ship0.png");
            break;
        case SHOOT:
            objectTexture = IMG_LoadTexture(window.renderer, "../data/ShipsPNG/shoot0.png");
            break;
        case FORWARD:
            objectTexture = IMG_LoadTexture(window.renderer, "../data/ShipsPNG/fwd0.png");
            break;
        case BACKWARDS:
            objectTexture = IMG_LoadTexture(window.renderer, "../data/ShipsPNG/back0.png");
            break;
        case CLOCKWISE_TURN:
            objectTexture = IMG_LoadTexture(window.renderer, "../data/ShipsPNG/clock.png");
            break;
        case COUNTER_TURN:
            objectTexture = IMG_LoadTexture(window.renderer, "../data/ShipsPNG/counter.png");
            break;
        case DESTROY:
            break;
//        case DAMAGED:
//            break;
        default:
            break;
    };
    SDL_Rect dstRect = {renderPosX, renderPosY, 32, 32};
    SDL_Rect srcRect = {0, 0, 32, 32};;
    SDL_RendererFlip flip;
////    SDL_Log("test");
    SDL_RenderCopyEx(window.renderer, objectTexture, &srcRect, &dstRect, angle, nullptr, flip);
}


//void Player::SetAnimState(Window &window) {
//    switch(currentAnimationState) {
//        case IDLE:
//            break;
//        case SHOOT:
//            break;
//        case FORWARD:
//            break;
//        case BACKWARDS:
//            break;
//        case CLOCKWISE_TURN:
//            break;
//        case COUNTER_TURN:
//            break;
//        case DESTROY:
//            break;
////        case DAMAGED:
////            break;
//        default:
//            break;
//
//    }
