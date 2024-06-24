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
    hp = 3; // TODO link to GEH
    name = "player";
}

void Player::Render(Window &window) {
    UpdateAnimState(window);
    SDL_Rect dstRect = {renderPosX, renderPosY, 32, 32};
    SDL_Rect srcRect = {0, 0, 32, 32};;
    SDL_RendererFlip flip = SDL_RendererFlip();
////    SDL_Log("test");
    SDL_RenderCopyEx(window.renderer, objectTexture, &srcRect, &dstRect, angle, nullptr, flip);
//    CollisionBox collisionBox = CollisionBox(&window, positionX, positionY, textureWidth, textureHeight, CollisionType::TerrainDestructible);
//    collisionBox.Render(window);

}


void Player::UpdateAnimState(Window &renderer) {
SDL_Log("%i", frameCounter);
// Modulo calc on sprites dependd on the length of a given animation
    switch (currentAnimationState) {
        case IDLE: // Always only one frame on idle
        frameCounter = 0;
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
            frameCounter = 0;
            objectTexture = IMG_LoadTexture(window->renderer, "../data/ShipsPNG/clock.png");
            break;
        case COUNTER_TURN:
            frameCounter = 0;
            objectTexture = IMG_LoadTexture(window->renderer, "../data/ShipsPNG/counter.png");
            break;
        case DAMAGED:
            if (!damaged) {
                damaged = true;
                animStateTtl = 8;
            } else {
                animStateTtl--;
                if (animStateTtl <= 0) {
                    currentAnimationState = IDLE;
                    damaged = false;
                    frameCounter = 0;
                }
            }
            SDL_Log("ttl = %i, state = %u", animStateTtl, currentAnimationState);
            objectTexture = IMG_LoadTexture(window->renderer, "../data/ShipsPNG/shield.png");
            break;
        case DESTROY:
            if(frameCounter < 4) {
                objectTexture = IMG_LoadTexture(window->renderer, "../data/ShipsPNG/destroy0.png");
            } else if (frameCounter < 8) {

                objectTexture = IMG_LoadTexture(window->renderer, "../data/ShipsPNG/destroy1.png");
            } else if (frameCounter < 12) {
                objectTexture = IMG_LoadTexture(window->renderer, "../data/ShipsPNG/destroy2.png");
            } else {
                    objectTexture = IMG_LoadTexture(window->renderer, "../data/ShipsPNG/boom.png");
            }
            break;
        default:
            break;
    }
//        case DAMAGED:
//            break;

    };



void Player::Damage(int dp) {
    currentAnimationState = DAMAGED;
    hp -= dp;
}

