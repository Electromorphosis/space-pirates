//
// Created by mechlon on 09.06.24.
//

#ifndef SPACE_PIRATES_WINDOW_H
#define SPACE_PIRATES_WINDOW_H
#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <vector>
#include "GameObject.h"
//#include "Particle.h"
#include <memory>

class GameObject;

class Window {
public:
    Window(int windowWidth, int windowHeight);
    int Width = 0;
    int Height = 0;
    ~Window();
    SDL_Window* window;
    SDL_Renderer* renderer;
    std::vector<std::unique_ptr<GameObject>> gameObjectsVector; // "Entities" such as rocks
    std::vector<std::unique_ptr<GameObject>> projectilesVector; // Laser beams
    std::vector<std::unique_ptr<GameObject>> particleEffectsVector; // Small VFXs
    std::unique_ptr<GameObject> player;

    void RenderAll();
    void TidyParticles();
    void TidyProjectiles();
    void TidyGameObjects();
    void CheckAllCollisions();

    bool checkIfTwoObjectsCollide(const std::unique_ptr<GameObject>& object1, const std::unique_ptr<GameObject>& object2);
};



#endif //SPACE_PIRATES_WINDOW_H
