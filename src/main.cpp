/**
 * This is the simple hello world for SDL2.
 * 
 * You need C++14 to compile this.
 */

#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
//#include <chrono>
#include <iostream>
#include <thread>
#include <vector>
#include "MovementUtility.h"

//// check for errors
//#define errcheck(e)                                                            \
//  {                                                                            \
//    if (e) {                                                                   \
//      cout << SDL_GetError() << endl;                                          \
//      SDL_Quit();                                                              \
//      return -1;                                                               \
//    }                                                                          \
//  }
std::vector<int> playerInGameCoords;
int x_player = 200;
int y_player = 200;
float velocity = 0;
std::vector<float> playerAbsoluteCoords;
float x_player_abs = 200.0;
float y_player_abs = 200.0;

int main(int , char **) {
  using namespace std;
  MovementUtility* movementUtility = new MovementUtility();
  playerInGameCoords.push_back(x_player);
  playerInGameCoords.push_back(y_player);
  playerAbsoluteCoords.push_back(x_player_abs);
  playerAbsoluteCoords.push_back(y_player_abs);
//  using namespace std::chrono;
  const int width = 500;
  const int height = 500;
    float DeltaTime = 0.4;
//  errcheck(SDL_Init(SDL_INIT_VIDEO) != 0);
int playerAngle = 0;
  SDL_Window *window = SDL_CreateWindow(
      "My Next Superawesome Game", SDL_WINDOWPOS_UNDEFINED,
      SDL_WINDOWPOS_UNDEFINED, width, height, SDL_WINDOW_SHOWN);
//  errcheck(window == nullptr);

  SDL_Renderer *renderer = SDL_CreateRenderer(
      window, -1, SDL_RENDERER_ACCELERATED);
//  errcheck(renderer == nullptr);

  int textureWidth = 32;
  int textureHeight = 32;
  SDL_Texture* objectTexture = IMG_LoadTexture(renderer, "../data/ShipsPNG/ship0.png");
  SDL_QueryTexture(objectTexture, NULL, NULL, &textureWidth, &textureHeight);
    Uint32 lastFrameTime = SDL_GetTicks();
    const Uint32 MS_PER_FRAME = 1000 / 60; // Limit FPS do 60


    //auto dt = 15ms;
//  milliseconds dt(15);

//  steady_clock::time_point current_time = steady_clock::now(); // remember current time
  for (bool game_active = true; game_active;) {
      SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255);
      SDL_RenderClear(renderer);

    SDL_Event event;
    while (SDL_PollEvent(&event)) { // check if there are some events
      if (event.type == SDL_QUIT)
        game_active = false;
    }

      const Uint8 *keyboardState = SDL_GetKeyboardState(NULL);

// Todo: Add velocity vector which is applied at the end of the scan, so that <<possibly>> it will work for multi-key combos
      if (keyboardState[SDL_SCANCODE_W]) {
          velocity += 0.1;
      }
      if (keyboardState[SDL_SCANCODE_S]) {
          velocity -= 0.1;
      }
      if (keyboardState[SDL_SCANCODE_A]) {
          playerAngle-=1;
      }
      if (keyboardState[SDL_SCANCODE_D]) {
          playerAngle+=1;
      }
        SDL_Log("Velocity: %f", velocity);
      SDL_Log("Angle: %i*", playerAngle);
      if (velocity < -0.5) velocity = -0.5;
      if (velocity > 1) velocity = 1;

      playerAngle %= 360;
      std::vector<float> newMovementVector = movementUtility->calculate(playerAngle);
//      SDL_Log("%f, %f", newMovementVector.at(0), newMovementVector.at(1));
      playerAbsoluteCoords.at(0) += newMovementVector.at(0) * velocity;
      playerAbsoluteCoords.at(1) -= newMovementVector.at(1) * velocity;
        x_player = static_cast<int>(playerAbsoluteCoords.at(0));
      y_player = static_cast<int>(playerAbsoluteCoords.at(1));

    SDL_SetRenderDrawColor(renderer, 0, 0, 0, 0);
    SDL_Rect kwadrat = {x_player, y_player, 10, 10};
    SDL_RenderFillRect(renderer, &kwadrat);

      SDL_Rect dstRect = { x_player, y_player, 32, 32 };
      SDL_Rect srcRect = { 0 , 0, 32, 32 };;
      SDL_RendererFlip flip;
    SDL_RenderCopyEx(renderer, objectTexture, &srcRect, &dstRect, playerAngle, nullptr, flip);


    SDL_RenderPresent(renderer); // draw frame to screen
      Uint32 currentFrameTime = SDL_GetTicks();
      Uint32 elapsedTime = currentFrameTime - lastFrameTime;

      if (elapsedTime < MS_PER_FRAME) {
          SDL_Delay(MS_PER_FRAME - elapsedTime);
      }

      lastFrameTime = SDL_GetTicks();

      DeltaTime = ((elapsedTime) / 1000.0f) + 0.001f;


//    this_thread::sleep_until(current_time = current_time + dt);
  }
  SDL_DestroyRenderer(renderer);
  SDL_DestroyWindow(window);
  SDL_Quit();
  return 0;
}

