//
// Created by mechlon on 09.06.24.
//

#include "Window.h"
#include <algorithm>
//#include "Particle.h"

Window::Window(int windowWidth, int windowHeight) {
    Width = windowWidth;
    Height = windowHeight;
    SDL_Init( SDL_INIT_EVERYTHING );
    SDL_CreateWindowAndRenderer( windowWidth, windowHeight,SDL_WINDOW_SHOWN, &window, &renderer);


}

Window::~Window() {
    SDL_DestroyRenderer(renderer);
    SDL_DestroyWindow(window);
    SDL_Quit();
}

void Window::RenderAll() {
    SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255);
    SDL_RenderClear(renderer);
    SDL_SetRenderDrawColor(renderer, 0, 0, 0, 0);

    for (const auto& gameObject : gameObjectsVector) {
        if (gameObject) {
            gameObject->Render(*this); // Dereference after null check
        }
    }

    this->TidyParticles();
    for (const auto& gameObject : particleEffectsVector) {
        if (gameObject) {
            gameObject->Render(*this); // Dereference after null check
        }
    }

    this->TidyProjectiles();
    for (const auto& gameObject : projectilesVector) {
        if (gameObject) {
            gameObject->Render(*this); // Dereference after null check
        }
    }

    player->Render(*this);

    SDL_RenderPresent(renderer); // draw frame to screen
}

void Window::TidyParticles() {
    particleEffectsVector.erase(
            std::remove_if(
                    particleEffectsVector.begin(),
                    particleEffectsVector.end(),
                    [](const std::unique_ptr<GameObject>& p) {
                        return p->ttl < 0;
                    }
            ),
            particleEffectsVector.end()
    );
}

void Window::TidyProjectiles() {
    // SDL_Log("Vector length pre-tidying: %zu", projectilesVector.size());
    projectilesVector.erase(
            std::remove_if(
                    projectilesVector.begin(),
                    projectilesVector.end(),
                    [this](const std::unique_ptr<GameObject>& p) {
                        return p->positionX <= -(static_cast<float>(Width)) || p->positionX >= (static_cast<float>(Width) * 1.5) ||
                               p->positionY <= -(static_cast<float>(Height)) || p->positionY >= (static_cast<float>(Height) * 1.5);
                    }
            ),
            projectilesVector.end()
    );
    // SDL_Log("Vector length post-tidying: %zu", projectilesVector.size());
}