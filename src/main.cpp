#include <SDL2/SDL.h>
#include <vector>
#include "MovementUtility.h"
#include "Player.h"
#include "Rock.h"
#include "Window.h"
#include "Particle.h"
#include <memory>
#include <random>


int main(int , char **) {
  using namespace std;
  MovementUtility* movementUtility = new MovementUtility();
    std::random_device rd;
    std::mt19937 gen(rd());
    std::uniform_int_distribution<> distrPartGen(0, 3);

  const int width = 500;
  const int height = 500;
    float DeltaTime;

    Window window(width, height);

//Player player(&window);
//std::unique_ptr<Player> player(new Player(&window));
Player* player = new Player(&window);
    window.player = std::unique_ptr<Player>(player);

////    Player& player;
//    if (window.gameObjectsVector.at(0)) { // Check if the vector is not empty
//        Player* playerPtr = static_cast<Player*>(window.gameObjectsVector.at(0).get());
////        player = *playerPtr; // Dereference the pointer and assign to the reference
//    }

    for (int i = 0; i < 8; i++) {
        window.gameObjectsVector.push_back(std::make_unique<Rock>(&window, "random"));
    }

    Uint32 lastFrameTime = SDL_GetTicks();

    const Uint32 MS_PER_FRAME = 1000 / 60; // Limit FPS do 60



  for (bool game_active = true; game_active;) {


    SDL_Event event;
    while (SDL_PollEvent(&event)) { // check if there are some events
      if (event.type == SDL_QUIT)
        game_active = false;
    }

      const Uint8 *keyboardState = SDL_GetKeyboardState(NULL);

// Todo: Add velocity vector which is applied at the end of the scan, so that <<possibly>> it will work for multi-key combos
      if (keyboardState[SDL_SCANCODE_W]) {
          player->velocity += 0.1;
      }
      if (keyboardState[SDL_SCANCODE_S]) {
          player->velocity -= 0.1;
      }
      if (keyboardState[SDL_SCANCODE_A]) {
          player->angle-=1;
      }
      if (keyboardState[SDL_SCANCODE_D]) {
          player->angle+=1;
      }
//        SDL_Log("Velocity: %f", player.velocity);
//      SDL_Log("Angle: %i*", player.angle);
      if (player->velocity < -0.5) player->velocity = -0.5;
      if (player->velocity > 1) player->velocity = 1;

      int partRoll = distrPartGen(gen);
      if (player->velocity != 0 && partRoll == 1) { window.gameObjectsVector.push_back(std::make_unique<Particle>(&window, player->positionX, player->positionY, 10,  "random"));
        SDL_Log("At x:%i, y:%i particle was generated!", window.gameObjectsVector.back()->renderPosX, window.gameObjectsVector.back()->renderPosY);
      }
      std::vector<float> newMovementVector = movementUtility->calculate(player->angle);
//      SDL_Log("%f, %f", newMovementVector.at(0), newMovementVector.at(1));
      player->positionX += newMovementVector.at(0) * player->velocity;
      player->positionY -= newMovementVector.at(1) * player->velocity;

      player->renderPosX = static_cast<int>(player->positionX);
      player->renderPosY = static_cast<int>(player->positionY);

//      SDL_Log("Player coordinates: {%i, %i}", player->renderPosX, player->renderPosY);

        window.RenderAll();
      Uint32 currentFrameTime = SDL_GetTicks();
      Uint32 elapsedTime = currentFrameTime - lastFrameTime;

      if (elapsedTime < MS_PER_FRAME) {
          SDL_Delay(MS_PER_FRAME - elapsedTime);
      }

      lastFrameTime = SDL_GetTicks();

      DeltaTime = ((elapsedTime) / 1000.0f) + 0.001f;


  }

  return 0;
}

