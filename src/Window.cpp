//
// Created by mechlon on 09.06.24.
//

#include "Window.h"
#include <algorithm>
#include <SDL2/SDL_ttf.h>

//#include "Particle.h"

Window::Window(GlobalEventHandler *_events, int windowWidth, int windowHeight) {
    geh = _events;
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

    this->TidyGameObjects();
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

    if (!renderMenu) {
        player->Render(*this);
        scoreTextBox->Render(*this);
        healthTextBox->Render(*this);
    }

    if (renderMenu) {
        RenderMenuHighlight();
    }

    for (const auto& textBox : textBoxesVector) {
        if (textBox) {
            textBox->Render(*this); // Dereference after null check
        }
    }
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
    // Remove lasers too far away
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

    // Remove lasers that hit the target
    projectilesVector.erase(
            std::remove_if(
                    projectilesVector.begin(),
                    projectilesVector.end(),
                    [this](const std::unique_ptr<GameObject>& p) {
                        return p-> hp < 0;
                    }
            ),
            projectilesVector.end()
    );
}

void Window::CheckAllCollisions() {
    // Loop through each projectile in the projectileVector
    for (auto& projectile : projectilesVector) {
        if (projectile) {
            for (auto& gameObject : gameObjectsVector) {
                if (gameObject) {
                    if (checkIfTwoObjectsCollide(projectile, gameObject)) {
//                        SDL_Log("Collision!");
                        gameObject->Damage(1);
                        projectile->Damage(1);
                }

            }
        }
    }}

        for (auto& gameObject : gameObjectsVector) {
        if (gameObject  ) {
            if (checkIfTwoObjectsCollide(gameObject, player)) {
                                        SDL_Log("Collision!");

                gameObject->Damage(20);
                player->Damage(1);
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
        } else if (object1->name == "asteroid" || object1->name == "standard_sprite" || object1->name == "player") {
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
        } else if (object2->name == "asteroid" || object2->name == "standard_sprite" || object2->name == "player") {
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

void Window::TidyGameObjects() {
    // SDL_Log("Vector length pre-tidying: %zu", projectilesVector.size());
    // Remove lasers too far away
    gameObjectsVector.erase(
            std::remove_if(
                    gameObjectsVector.begin(),
                    gameObjectsVector.end(),
                    [this](const std::unique_ptr<GameObject>& p) {
                        return p->positionX <= -(static_cast<float>(Width)) || p->positionX >= (static_cast<float>(Width) * 1.5) ||
                               p->positionY <= -(static_cast<float>(Height)) || p->positionY >= (static_cast<float>(Height) * 1.5);
                    }
            ),
            gameObjectsVector.end()
    );
    // SDL_Log("Vector length post-tidying: %zu", projectilesVector.size());

    // Remove GameObjects being hit the target
    gameObjectsVector.erase(
            std::remove_if(
                    gameObjectsVector.begin(),
                    gameObjectsVector.end(),
                    [this](const std::unique_ptr<GameObject>& p) {
                        return p-> hp < 0;
                    }
            ),
            gameObjectsVector.end()
    );
}

void Window::UpdateGui() {
    scoreTextBox->content = "SCORE : " + std::to_string(geh->score);
    healthTextBox->content = "HP : " + std::to_string(player->hp);
}

void Window::RenderMenuHighlight() {
    SDL_Rect rect;
switch(menuHighlight) {
    case 0: // MAIN MENU
        SDL_SetRenderDrawColor(renderer, 0, 255, 0, 255);
        rect = { static_cast<int>(Width*0.30), static_cast<int>(Height*0.45), static_cast<int>(Width-(Width*0.6)), Height/9 };
        SDL_RenderDrawLine(renderer, rect.x, rect.y, rect.x + rect.w, rect.y); // Top line
        SDL_RenderDrawLine(renderer, rect.x, rect.y + rect.h, rect.x + rect.w, rect.y + rect.h); // Bottom line
        SDL_RenderDrawLine(renderer, rect.x, rect.y, rect.x, rect.y + rect.h); // Left line
        SDL_RenderDrawLine(renderer, rect.x + rect.w, rect.y, rect.x + rect.w, rect.y + rect.h); // Right line
        break;
    case 1: // LEADERBOARDS
        SDL_SetRenderDrawColor(renderer, 0, 255, 0, 255);
        rect = { static_cast<int>(Width*0.10), static_cast<int>(Height*0.55), static_cast<int>(Width-(Width*0.2)), Height/9 };
        SDL_RenderDrawLine(renderer, rect.x, rect.y, rect.x + rect.w, rect.y); // Top line
        SDL_RenderDrawLine(renderer, rect.x, rect.y + rect.h, rect.x + rect.w, rect.y + rect.h); // Bottom line
        SDL_RenderDrawLine(renderer, rect.x, rect.y, rect.x, rect.y + rect.h); // Left line
        SDL_RenderDrawLine(renderer, rect.x + rect.w, rect.y, rect.x + rect.w, rect.y + rect.h); // Right line
        break;
    case 2: // HELP
        SDL_SetRenderDrawColor(renderer, 0, 255, 0, 255);
        rect = { static_cast<int>(Width*0.35), static_cast<int>(Height*0.65), static_cast<int>(Width-(Width*0.7)), Height/9 };
        SDL_RenderDrawLine(renderer, rect.x, rect.y, rect.x + rect.w, rect.y); // Top line
        SDL_RenderDrawLine(renderer, rect.x, rect.y + rect.h, rect.x + rect.w, rect.y + rect.h); // Bottom line
        SDL_RenderDrawLine(renderer, rect.x, rect.y, rect.x, rect.y + rect.h); // Left line
        SDL_RenderDrawLine(renderer, rect.x + rect.w, rect.y, rect.x + rect.w, rect.y + rect.h); // Right line
        break;
    case 3: // QUIT
        SDL_SetRenderDrawColor(renderer, 0, 255, 0, 255);
        rect = { static_cast<int>(Width*0.35), static_cast<int>(Height*0.75), static_cast<int>(Width-(Width*0.7)), Height/9 };
        SDL_RenderDrawLine(renderer, rect.x, rect.y, rect.x + rect.w, rect.y); // Top line
        SDL_RenderDrawLine(renderer, rect.x, rect.y + rect.h, rect.x + rect.w, rect.y + rect.h); // Bottom line
        SDL_RenderDrawLine(renderer, rect.x, rect.y, rect.x, rect.y + rect.h); // Left line
        SDL_RenderDrawLine(renderer, rect.x + rect.w, rect.y, rect.x + rect.w, rect.y + rect.h); // Right line
        break;
    default:
        break;
}
}

void Window::RestartRenderer() {
    gameObjectsVector.clear();
    projectilesVector.clear();
    particleEffectsVector.clear();
    textBoxesVector.clear();
    player = nullptr;
    scoreTextBox = nullptr;
    healthTextBox = nullptr;
    SDL_RenderClear(renderer);
}
