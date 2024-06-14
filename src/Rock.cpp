//
// Created by mechlon on 09.06.24.
//

#include "Rock.h"
#include "Window.h"
#include <iostream>
#include <random>

Rock::Rock(Window* _window) {
    window = _window;
    objectTexture = IMG_LoadTexture(window->renderer, "../data/ShipsPNG/rock.png");
    SDL_QueryTexture(objectTexture, NULL, NULL, &textureWidth, &textureHeight);

}

Rock::Rock(Window* _window, std::string spawn) {
    std::random_device rd;
    std::mt19937 gen(rd());
    if (spawn == "random") {
        std::uniform_int_distribution<> distr(0, 500-textureHeight); // Todo: dynamic for width/height, though that might not be needed for now.
        renderPosX = distr(gen);
        renderPosY = distr(gen);
        std::uniform_int_distribution<> distr2(0, 360);
        angle = distr2(gen);
    }
    window = _window;
    objectTexture = IMG_LoadTexture(window->renderer, "../data/ShipsPNG/rock.png");
    SDL_QueryTexture(objectTexture, NULL, NULL, &textureWidth, &textureHeight);

}

void Rock::Render(Window &window) {

//    SDL_Rect kwadrat = {renderPosX, renderPosY, 10, 10};
//    SDL_RenderFillRect(renderer, &kwadrat);

    SDL_Rect dstRect = { renderPosX, renderPosY, 32, 32 };
    SDL_Rect srcRect = { 0 , 0, 32, 32 };;
    SDL_RendererFlip flip;
    SDL_RenderCopyEx(window.renderer, objectTexture, &srcRect, &dstRect, angle, nullptr, flip);

}