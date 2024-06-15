//
// Created by mechlon on 09.06.24.
//

#include "Particle.h"
#include "Window.h"
#include <iostream>
#include <random>
#include <SDL2/SDL_render.h>

Particle::Particle(Window* _window) {
    window = _window;
    objectTexture = IMG_LoadTexture(window->renderer, "../data/ShipsPNG/particle.png");
    SDL_QueryTexture(objectTexture, NULL, NULL, &textureWidth, &textureHeight);

}

Particle::Particle(Window* _window, float posX, float posY, int dispersionRate, std::string spawn, bool randCol) {
    // Default position are used as a central point position for the spawner - the actual position will rely on dispersionRate param value
    // with randomization.
    window = _window;
    objectTexture = IMG_LoadTexture(window->renderer, "../data/ShipsPNG/particle.png");

    positionX = posX;
    positionY = posY;
    testStartPosX = static_cast<int>(positionX);
    testStartPosY = static_cast<int>(positionY);
    std::random_device rd;
    std::mt19937 gen(rd());
    if (spawn == "random") {
        std::uniform_int_distribution<> distrX(static_cast<int>(positionX)+16-dispersionRate, static_cast<int>(positionX)+16+dispersionRate); // Todo: dynamic for width/height, though that might not be needed for now.
        renderPosX = distrX(gen);
        positionX = static_cast<float>(renderPosX);
        std::uniform_int_distribution<> distrY(static_cast<int>(positionY)+16-dispersionRate, static_cast<int>(positionY)+16+dispersionRate);
        renderPosY = distrY(gen);
        positionY = static_cast<float>(renderPosY);
        std::uniform_int_distribution<> distrAngle(0, 360);
        angle = distrAngle(gen);
        std::uniform_int_distribution<> distrTtl(50, 100);
        ttl = distrTtl(gen);
        if (randCol) {
            std::uniform_int_distribution<> distrTexMod(50, 250);
            Uint8 texModValue = static_cast<Uint8>(distrTexMod(gen));
            SDL_SetTextureColorMod(objectTexture, texModValue, 100, 100);
        }
    }
    SDL_QueryTexture(objectTexture, NULL, NULL, &textureWidth, &textureHeight);
}

Particle::~Particle() {
}

void Particle::Render(Window &window) {

if (ttl > 0) {
    this->ttl -= 1;
//    return;
} else if (ttl == 0) {
//    SDL_Log("Particle expired");
    return;
}

    SDL_Rect dstRect = { renderPosX, renderPosY, 2, 2 };
    SDL_Rect srcRect = { 0 , 0, 2, 2 };;
    SDL_RendererFlip flip;
    SDL_RenderCopyEx(window.renderer, objectTexture, &srcRect, &dstRect, angle, nullptr, flip);

//    // Debug red dot
//    SDL_SetRenderDrawColor( window.renderer, 255, 0, 0, 255 );
//    SDL_Rect r;
//    r.x = testStartPosX;
//    r.y = testStartPosY;
//    r.w = 2;
//    r.h = 2;
//
//    SDL_RenderFillRect( window.renderer, &r );
//    SDL_SetRenderDrawColor( window.renderer, 0, 0, 0, 255 );

}