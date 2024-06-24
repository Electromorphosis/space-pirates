
#ifndef SPACE_PIRATES_WINDOW_H
#define SPACE_PIRATES_WINDOW_H

#include <vector>
#include <memory>

#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>

#include "GameObject.h"
#include "TextBox.h"
#include "GlobalEventHandler.h"

class GameObject;
class TextBox;

class Window {
public:
    Window(GlobalEventHandler* _events, int windowWidth, int windowHeight);
    ~Window();

    void RenderAll();
    void TidyParticles();
    void TidyProjectiles();
    void TidyGameObjects();
    void CheckAllCollisions();
    void UpdateGui();
    void RenderMenuHighlight();
    void RestartRenderer();
    bool checkIfTwoObjectsCollide(const std::unique_ptr<GameObject>& object1, const std::unique_ptr<GameObject>& object2);

    std::vector<std::unique_ptr<GameObject>> gameObjectsVector; // "Entities" such as rocks
    std::vector<std::unique_ptr<GameObject>> projectilesVector; // Laser beams
    std::vector<std::unique_ptr<GameObject>> particleEffectsVector; // Small VFXs - particle effects
    std::vector<std::unique_ptr<TextBox>> textBoxesVector; // VariousNonConstantTextBoxes
    std::unique_ptr<TextBox> scoreTextBox; // UI elements: player's score
    std::unique_ptr<TextBox> healthTextBox; // UI elements: player's HP
    std::unique_ptr<GameObject> player;

    SDL_Window* window;
    SDL_Renderer* renderer;
    GlobalEventHandler* geh;

    bool renderMenu = true;
    int Width = 0;
    int Height = 0;
    int menuHighlight = 0;
    int score = 0;
};

#endif //SPACE_PIRATES_WINDOW_H
