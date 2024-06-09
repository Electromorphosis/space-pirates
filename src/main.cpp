#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <vector>
#include "MovementUtility.h"
#include "Player.h"


int main(int , char **) {
  using namespace std;
  MovementUtility* movementUtility = new MovementUtility();


  const int width = 500;
  const int height = 500;
    float DeltaTime;
  SDL_Window *window = SDL_CreateWindow(
      "My Next Superawesome Game", SDL_WINDOWPOS_UNDEFINED,
      SDL_WINDOWPOS_UNDEFINED, width, height, SDL_WINDOW_SHOWN);

  SDL_Renderer *renderer = SDL_CreateRenderer(
      window, -1, SDL_RENDERER_ACCELERATED);

    Player player;
    player.objectTexture = IMG_LoadTexture(renderer, "../data/ShipsPNG/ship0.png");
    SDL_QueryTexture(player.objectTexture, NULL, NULL, &player.textureWidth, &player.textureHeight);

    int x_player_render;
    int y_player_render;
    Uint32 lastFrameTime = SDL_GetTicks();

    const Uint32 MS_PER_FRAME = 1000 / 60; // Limit FPS do 60



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
          player.velocity += 0.1;
      }
      if (keyboardState[SDL_SCANCODE_S]) {
          player.velocity -= 0.1;
      }
      if (keyboardState[SDL_SCANCODE_A]) {
          player.angle-=1;
      }
      if (keyboardState[SDL_SCANCODE_D]) {
          player.angle+=1;
      }
//        SDL_Log("Velocity: %f", player.velocity);
//      SDL_Log("Angle: %i*", player.angle);
      if (player.velocity < -0.5) player.velocity = -0.5;
      if (player.velocity > 1) player.velocity = 1;


      std::vector<float> newMovementVector = movementUtility->calculate(player.angle);
//      SDL_Log("%f, %f", newMovementVector.at(0), newMovementVector.at(1));
      player.positionX += newMovementVector.at(0) * player.velocity;
      player.positionY -= newMovementVector.at(1) * player.velocity;
        x_player_render = static_cast<int>(player.positionX);
      y_player_render = static_cast<int>(player.positionY);

      SDL_Log("Player coordinates: {%i, %i}", x_player_render, y_player_render);
    SDL_SetRenderDrawColor(renderer, 0, 0, 0, 0);
    SDL_Rect kwadrat = {x_player_render, y_player_render, 10, 10};
    SDL_RenderFillRect(renderer, &kwadrat);

      SDL_Rect dstRect = { x_player_render, y_player_render, 32, 32 };
      SDL_Rect srcRect = { 0 , 0, 32, 32 };;
      SDL_RendererFlip flip;
    SDL_RenderCopyEx(renderer, player.objectTexture, &srcRect, &dstRect, player.angle, nullptr, flip);


    SDL_RenderPresent(renderer); // draw frame to screen
      Uint32 currentFrameTime = SDL_GetTicks();
      Uint32 elapsedTime = currentFrameTime - lastFrameTime;

      if (elapsedTime < MS_PER_FRAME) {
          SDL_Delay(MS_PER_FRAME - elapsedTime);
      }

      lastFrameTime = SDL_GetTicks();

      DeltaTime = ((elapsedTime) / 1000.0f) + 0.001f;


  }
  SDL_DestroyRenderer(renderer);
  SDL_DestroyWindow(window);
  SDL_Quit();
  return 0;
}

