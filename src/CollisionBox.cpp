//
// Created by mechlon on 15.06.24.
//
#include "SDL2/SDL_image.h"
#include "SDL2/SDL_render.h"
#include "CollisionBox.h"
#include "CollisionType.h"
#include <string>

CollisionBox::CollisionBox(Window *_window, float posX, float posY, int initWidth, int initHeight, CollisionType ct) {
    window = _window;
    positionX = posX;
    positionY = posY;
    renderPosX = static_cast<int>(positionX);
    renderPosY = static_cast<int>(positionY);
    width = initWidth;
    height = initHeight;
    boxCollisionType = ct;
}

void CollisionBox::UpdatePosition(float newPosX, float newPosY) {
    positionX = newPosX;
    positionY = newPosY;
    renderPosX = static_cast<int>(positionX);
    renderPosY = static_cast<int>(positionY);
}


void CollisionBox::Render(Window& renderWindow) {
    if(boxCollisionType == CollisionType::TerrainDestructible) {
        SDL_SetRenderDrawColor(renderWindow.renderer, 0, 255, 0, 255);
    } else if(boxCollisionType == CollisionType::FriendlyProjectile) {
        SDL_SetRenderDrawColor(renderWindow.renderer, 255, 0, 0, 255);
    }

//    SDL_Log("Render pos: %i, %i ; width: %i, height: %i", renderPosX, renderPosY, width, height);
    SDL_Rect rect = { renderPosX, renderPosY, width, height }; // x, y, width, height

    // Draw the outline of the rectangle using horizontal and vertical lines
    SDL_RenderDrawLine(renderWindow.renderer, rect.x, rect.y, rect.x + rect.w, rect.y); // Top line
    SDL_RenderDrawLine(renderWindow.renderer, rect.x, rect.y + rect.h, rect.x + rect.w, rect.y + rect.h); // Bottom line
    SDL_RenderDrawLine(renderWindow.renderer, rect.x, rect.y, rect.x, rect.y + rect.h); // Left line
    SDL_RenderDrawLine(renderWindow.renderer, rect.x + rect.w, rect.y, rect.x + rect.w, rect.y + rect.h); // Right line
    SDL_SetRenderDrawColor(renderWindow.renderer, 0, 0, 0, 255);
}

void CollisionBox::Damage(int dp) {

}
