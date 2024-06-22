//
// Created by mechlon on 15.06.24.
//

#include "LaserBeam.h"
#include "CollisionBox.h"

LaserBeam::LaserBeam(Window *_window, float posX, float posY, int initAngle) {
    window = _window;
    objectTexture = IMG_LoadTexture(window->renderer, "../data/blueLaser.png");
    SDL_QueryTexture(objectTexture, NULL, NULL, &textureWidth, &textureHeight);
    positionX = posX + 16;
    positionY = posY + 16;
    renderPosX = static_cast<int>(positionX);
    renderPosY = static_cast<int>(positionY);
    angle = initAngle;
//    SDL_Log("Laser beam created at %f, %f {render: %d, %d }", positionX, positionY, renderPosX, renderPosY);
if (angle > 315 && angle <= 45 || angle > 135 && angle <= 225 ) {
    collisionBox = CollisionBox(window, positionX, positionY, textureWidth, textureHeight, CollisionType::FriendlyProjectile);
} else {
    collisionBox = CollisionBox(window, positionX, positionY, textureHeight, textureWidth, CollisionType::FriendlyProjectile);
}
    if(collisionBox.boxCollisionType == CollisionType::FriendlyProjectile) {
//        SDL_Log("Box created at: %f, %f", positionX, positionY);
    }
    hp = 0;
    name = "laser";

}


void LaserBeam::Render(Window &window) {
    if (hp < 0) {
        delete this;
        return;
    }
//    SDL_Log("Laser beam rendered at %f, %f {render: %i, %i }", positionX, positionY, renderPosX, renderPosY);
    SDL_Rect dstRect = { renderPosX, renderPosY, textureWidth, textureHeight };
    SDL_Rect srcRect = { 0 , 0, textureWidth, textureHeight };;
    SDL_RendererFlip flip = SDL_RendererFlip();
    SDL_RenderCopyEx(window.renderer, objectTexture, &srcRect, &dstRect, angle, nullptr, flip);

    // Debug - render collision box
    updateCollisionBox();
    collisionBox.Render(window);
}

LaserBeam::~LaserBeam() {
}
//
//void LaserBeam::UpdateCollision() {
//}

void LaserBeam::CheckCollision(CollisionType ct) {

}

void LaserBeam::updateCollisionBox() {
    collisionBox.UpdatePosition(positionX, positionY);
}

void LaserBeam::Damage() {
    hp--;
}
