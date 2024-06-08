/**
 * This is the simple hello world for SDL2.
 * 
 * You need C++14 to compile this.
 */

#include <SDL2/SDL.h>
//#include <SDL2/SDL_image.h>
//#include <chrono>
//#include <iostream>
//#include <thread>
#include "Window.h"
#include "EventSystem.h"
#include "WorldMap.h"
#include "TextureManager.h"

int main(int , char **) {
    using namespace std;
    GlobalSettings& globalSettings = GlobalSettings::GetInstance();

    bool gameRunning = true;
    float deltaTime = 0.4;

    Uint32 lastFrameTime = SDL_GetTicks();

    Window window = Window();

    // Init game engine (sub)systems
    EventSystem& eventSystem = EventSystem::GetInstance();
    WorldMap worldMap = WorldMap();
    TextureManager textureManager = TextureManager();

    // Init starting stuff
    Player player = new Player(window, new Visible(window.getRenderer(), TextureData *textureDataProvided))
    worldMap.getAllGameObjects().push_back(new WorldMap::MappedObject()))

    while(gameRunning) {

        // Event Grabber
        int polledSdlEvent;
        while ((polledSdlEvent = SDL_PollEvent(eventSystem.sdlEventObjectRef)) != 0) {
            if (polledSdlEvent == SDL_QUIT) {
                gameRunning = false;
            }
        }

        const Uint8 *keyboardState = SDL_GetKeyboardState(NULL);
        if (keyboardState[SDL_SCANCODE_W]) {
            y_player-=velocity;
        } else if (keyboardState[SDL_SCANCODE_S]) {
            y_player+=velocity;
        } else if (keyboardState[SDL_SCANCODE_A]) {
            x_player-=velocity;
        } else if (keyboardState[SDL_SCANCODE_D]) {
            x_player+=velocity;
        }

        window.RenderAll();

        // Time handling
        Uint32 currentFrameTime = SDL_GetTicks();
        Uint32 elapsedTime = currentFrameTime - lastFrameTime;
        Uint32 framerate = globalSettings.GetFramerate();

        if (elapsedTime < framerate) {
            SDL_Delay(framerate - elapsedTime);
        }

        lastFrameTime = SDL_GetTicks();
        deltaTime = ((elapsedTime) / 1000.0f) + 0.001f;
    }

    return 0;
}

