//
// Created by mechlon on 09.06.24.
//

#include "Rock.h"
#include "Window.h"
#include <iostream>
#include <random>
#include <cstdlib>

Rock::Rock(Window* _window, GlobalEventHandler* _events) {
    // Please note that this is practically unused
    window = _window;
    geh = _events;
//    collisionBox = CollisionBox(window, positionX, positionY, textureWidth, textureHeight, CollisionType::TerrainDestructible);
    objectTexture = IMG_LoadTexture(window->renderer, "../data/ShipsPNG/rock.png");
    SDL_QueryTexture(objectTexture, NULL, NULL, &textureWidth, &textureHeight);

}

Rock::Rock(Window* _window, GlobalEventHandler* _events, std::string spawn) {
    geh = _events;
    std::random_device rd;
    std::mt19937 gen(rd());
    renderPosX = 250;
    renderPosY = 250;
    while(abs(renderPosX-250) < 30 && abs(renderPosY-250) < 30  ) {
        if (spawn == "random") {
            std::uniform_int_distribution<> distr(0, 500 -
                                                     textureHeight); // Todo: dynamic for width/height, though that might not be needed for now.
            renderPosX = distr(gen);
            renderPosY = distr(gen);
            std::uniform_int_distribution<> distr2(0, 360);
            angle = distr2(gen);
        }
    }
    window = _window;
    objectTexture = IMG_LoadTexture(window->renderer, "../data/ShipsPNG/rock.png");
    SDL_QueryTexture(objectTexture, NULL, NULL, &textureWidth, &textureHeight);

    positionX = static_cast<int>(renderPosX);
    positionY = static_cast<int>(renderPosY);
//    collisionBox = CollisionBox(window, positionX, positionY, textureWidth, textureHeight, CollisionType::TerrainDestructible);
    hp = 2;
    ttl = -1;
    name = "standard_sprite";
}

Rock::~Rock() {
SDL_Log("Rock removed");
    delete objectTexture;
    delete window;
}

void Rock::Render(Window &window) {
    if (hp == 0) {
        objectTexture = IMG_LoadTexture(window.renderer, "../data/ShipsPNG/boom.png");
        ttl = 5;
        hp--;
        geh->score++;
    }
    if (ttl > 0) {
//        SDL_Log("Rock TTL = %i", ttl);
        ttl--;
    } else if (ttl == 0) {
        delete this;
        return;
    }
//    if (name == "asteroid") {
//        SDL_Log("[Rock Renderer] x pos = %f, y pos = %f, x rend = %i, y rend = %i", positionX, positionY, renderPosX, renderPosY);
//    }

    SDL_Rect dstRect = { renderPosX, renderPosY, 32, 32 };
    SDL_Rect srcRect = { 0 , 0, 32, 32 };;
    SDL_RendererFlip flip = SDL_RendererFlip();
    SDL_RenderCopyEx(window.renderer, objectTexture, &srcRect, &dstRect, angle, nullptr, flip);

    // debug - render collision box
//    collisionBox.Render(window);
}

void Rock::Damage(int dp) {
    hp -= dp;
}

Rock::Rock(Window *_window, GlobalEventHandler *_events, int face, int initAngle, int spawnPoint, const std::string& spawn) {
    std::random_device rd;
    std::mt19937 gen(rd());
    std::uniform_int_distribution<> distrVelocity(0, 5);
    geh = _events;
    positionX = 0;
    positionY = 0;
    renderPosX = 0;
    renderPosY = 0;

    if (spawn == "asteroid") {
        name = "asteroid";
        movable = true;
        hp = -1;
        switch(face) {
            case 0: // UP
                positionX = static_cast<float>(spawnPoint);
                positionY = static_cast<float>(-50);
//                SDL_Log("Starting coords: X= %f , Y=%f", positionX, positionY);
                angle = -initAngle;
                break;
            case 1: // RIGHT
                positionX = static_cast<float>(_window->Width + 50);
                positionY = static_cast<float>(spawnPoint);
                angle = initAngle - 180;
                break;
            case 2: // DOWN
                positionX = static_cast<float>(spawnPoint);
                positionY = static_cast<float>(_window->Height + 50);
                angle = initAngle;
                break;
            case 3: // LEFT
                positionX = -50;
                positionY = static_cast<float>(spawnPoint);
                angle = initAngle + 90;
                break;
            default:
                return;
        }
        velocity = 2;
//                distrVelocity(gen);
    }
    window = _window;
    objectTexture = IMG_LoadTexture(window->renderer, "../data/ShipsPNG/rock.png");
    SDL_QueryTexture(objectTexture, NULL, NULL, &textureWidth, &textureHeight);
    renderPosX = static_cast<int>(positionX);
    renderPosY = static_cast<int>(positionY);
//    SDL_Log("Starting coords (render/int): X= %i , Y=%i", renderPosX, renderPosY);
//    collisionBox = CollisionBox(window, positionX, positionY, textureWidth, textureHeight, CollisionType::TerrainDestructible);
    hp = 1;
    ttl = -1;
    name = "asteroid";
//    SDL_Log("Random rock spawned. Face: %i Angle: %i Velocity: %i SpawnPos: %i ", face, initAngle, velocity, spawnPoint);

}
