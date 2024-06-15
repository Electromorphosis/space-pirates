//
// Created by mechlon on 15.06.24.
//

#include "LaserBeam.h"
#include "CollisionBox.h"

LaserBeam::LaserBeam(Window *_window, float posX, float posY, int initAngle)
: collisionBox(window, positionX+3, positionY, 3, textureHeight, CollisionType::FriendlyProjectile)
{
    window = _window;
    objectTexture = IMG_LoadTexture(window->renderer, "../data/blueLaser.png");
    SDL_QueryTexture(objectTexture, NULL, NULL, &textureWidth, &textureHeight);
    positionX = posX + 16;
    positionY = posY + 16;
    renderPosX = static_cast<int>(positionX);
    renderPosY = static_cast<int>(positionY);
    angle = initAngle;
//    SDL_Log("Laser beam created at %f, %f {render: %d, %d }", positionX, positionY, renderPosX, renderPosY);
}


void LaserBeam::Render(Window &window) {
//    SDL_Log("Laser beam rendered at %f, %f {render: %i, %i }", positionX, positionY, renderPosX, renderPosY);
    SDL_Rect dstRect = { renderPosX, renderPosY, textureWidth, textureHeight };
    SDL_Rect srcRect = { 0 , 0, textureWidth, textureHeight };;
    SDL_RendererFlip flip;
    SDL_RenderCopyEx(window.renderer, objectTexture, &srcRect, &dstRect, angle, nullptr, flip);

    // Debug - render collision box
//    collisionBox.Render(window);
}

LaserBeam::~LaserBeam() {
}
