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
    UpdateAnimState(window);
    SDL_Rect dstRect = {renderPosX, renderPosY, 32, 32};
    SDL_Rect srcRect = {0, 0, 32, 32};;
    SDL_RendererFlip flip;
////    SDL_Log("test");
    SDL_RenderCopyEx(window.renderer, objectTexture, &srcRect, &dstRect, angle, nullptr, flip);
}


void Player::UpdateAnimState(Window &renderer) {

// Modulo calc on sprites dependd on the length of a given animation
    SDL_Log("%i", frameCounter);
    switch (currentAnimationState) {
        case IDLE: // Always only one frame on idle
            objectTexture = IMG_LoadTexture(window->renderer, "../data/ShipsPNG/ship0.png");
            break;
        case SHOOT: // 3 frames
            frameCounter %= 3;
            switch(frameCounter) {
                case 0:
                    objectTexture = IMG_LoadTexture(window->renderer, "../data/ShipsPNG/shoot0.png");
                    break;
                case 1:
                    objectTexture = IMG_LoadTexture(window->renderer, "../data/ShipsPNG/shoot1.png");
                    break;
                case 2:
                    objectTexture = IMG_LoadTexture(window->renderer, "../data/ShipsPNG/shoot2.png");
                    currentAnimationState = IDLE;
                    break;
                default: // "Booms" are de facto debugging mechanism
                    objectTexture = IMG_LoadTexture(window->renderer, "../data/ShipsPNG/boom.png");
                    break;
            }
            break;
        case FORWARD:
            frameCounter %= 3;
            switch(frameCounter) {
                case 0:
                    objectTexture = IMG_LoadTexture(window->renderer, "../data/ShipsPNG/fwd0.png");
                    break;
                case 1:
                    objectTexture = IMG_LoadTexture(window->renderer, "../data/ShipsPNG/fwd1.png");
                    break;
                case 2:
                    objectTexture = IMG_LoadTexture(window->renderer, "../data/ShipsPNG/fwd2.png");
                    break;
                default: // "Booms" are de facto debugging mechanism
                    objectTexture = IMG_LoadTexture(window->renderer, "../data/ShipsPNG/boom.png");
                    break;
            }
            break;
        case BACKWARDS:
            frameCounter %= 3;
            switch(frameCounter) {
                case 0:
                    objectTexture = IMG_LoadTexture(window->renderer, "../data/ShipsPNG/back0.png");
                    break;
                case 1:
                    objectTexture = IMG_LoadTexture(window->renderer, "../data/ShipsPNG/back1.png");
                    break;
                case 2:
                    objectTexture = IMG_LoadTexture(window->renderer, "../data/ShipsPNG/back2.png");
                    break;
                default: // "Booms" are de facto debugging mechanism
                    objectTexture = IMG_LoadTexture(window->renderer, "../data/ShipsPNG/boom.png");
                    break;
            }
            break;
        case CLOCKWISE_TURN:
            objectTexture = IMG_LoadTexture(window->renderer, "../data/ShipsPNG/clock.png");
            break;
        case COUNTER_TURN:
            objectTexture = IMG_LoadTexture(window->renderer, "../data/ShipsPNG/counter.png");
            break;
        case DESTROY:
            frameCounter %= 3;
            switch(frameCounter) {
                case 0:
                    objectTexture = IMG_LoadTexture(window->renderer, "../data/ShipsPNG/destroy0.png");
                    break;
                case 1:
                    objectTexture = IMG_LoadTexture(window->renderer, "../data/ShipsPNG/destroy1.png");
                    break;
                case 2:
                    objectTexture = IMG_LoadTexture(window->renderer, "../data/ShipsPNG/destroy2.png");
                    break;
                default: // "Booms" are de facto debugging mechanism
                    objectTexture = IMG_LoadTexture(window->renderer, "../data/ShipsPNG/boom.png");
                    break;
            }
            break;
//        case DAMAGED:
//            break;
        default:
            break;
    };

}
