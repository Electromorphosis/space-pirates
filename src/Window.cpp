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


    for (const auto& gameObject : particleEffectsVector) {
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
                    [](const std::unique_ptr<GameObject>& p) { // Capture by const reference
                        return p->ttl <= 0; // put your condition here
                    }
            ),
            particleEffectsVector.end()
    );
}