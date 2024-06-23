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
#include "TextBox.h"
#include <memory>
#include "GlobalEventHandler.h"

class GameObject;
class TextBox;

class Window {
public:
    Window(GlobalEventHandler* _events, int windowWidth, int windowHeight);
    int Width = 0;
    int Height = 0;
    int score = 0;
    ~Window();
    SDL_Window* window;
    SDL_Renderer* renderer;
    GlobalEventHandler* geh;
    std::vector<std::unique_ptr<GameObject>> gameObjectsVector; // "Entities" such as rocks
    std::vector<std::unique_ptr<GameObject>> projectilesVector; // Laser beams
    std::vector<std::unique_ptr<GameObject>> particleEffectsVector; // Small VFXs
    std::unique_ptr<TextBox> scoreTextBox; // UI elements: player's score
    std::unique_ptr<GameObject> player;

    void RenderAll();
    void TidyParticles();
    void TidyProjectiles();
    void TidyGameObjects();
    void CheckAllCollisions();
    void UpdateScore();

    bool checkIfTwoObjectsCollide(const std::unique_ptr<GameObject>& object1, const std::unique_ptr<GameObject>& object2);
};



#endif //SPACE_PIRATES_WINDOW_H
