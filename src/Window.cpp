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

    this->TidyProjectiles();
    for (const auto& gameObject : projectilesVector) {
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

void Window::CheckAllCollisions() {
    // Loop through each projectile in the projectileVector
    for (auto& projectile : projectilesVector) {
        if (projectile) {
            for (auto& gameObject : gameObjectsVector) {
                if (gameObject) {
                    bool collision = checkIfTwoObjectsCollide(projectile, gameObject);
                    if (collision) {
                        SDL_Log("Collision!");
//                        gameObject->Damage();
//                        projectile->Damage();
                    }
                }

            }
        }
    }
}

bool Window::checkIfTwoObjectsCollide(const std::unique_ptr<GameObject> &object1, const std::unique_ptr<GameObject> &object2) {
    {
        int o1_x = object1->renderPosX;
        int o1_y = object1->renderPosY;
        int o1_width = 0;
        int o1_height = 0;
        if (object1->name == "laser") { // Turbo-shady but well xD
            o1_width = 9;
            o1_height = 9;
        } else if (object1->name == "standard_sprite") {
            o1_width = 32;
            o1_height = 32;
        }
        int o2_x = object2->renderPosX;
        int o2_y = object2->renderPosY;
        int o2_width = 0;
        int o2_height = 0;
        if (object2->name == "laser") { // Turbo-shady but well xD
            o2_width = 9;
            o2_height = 9;
        } else if (object2->name == "standard_sprite") {
            o2_width = 32;
            o2_height = 32;
        }

//        SDL_Log("Object1 x : %i, y : %i, width : %i, height : %i", o1_x, o1_y, o1_width, o1_height);
//        SDL_Log("Object2 x : %i, y : %i, width : %i, height : %i", o2_x, o2_y, o2_width, o2_height);
        // Check for overlap on both X and Y axes
        return (o1_x < o2_x + o2_width &&
                o1_x + o1_width > o2_x &&
                o1_y < o2_y + o2_height &&
                o1_y + o1_height > o2_y);
    };
}
