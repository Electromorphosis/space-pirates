/**
 * This is the simple hello world for SDL2.
 * 
 * You need C++14 to compile this.
 */

#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <chrono>
#include <iostream>
#include <thread>

// check for errors
#define errcheck(e)                                                            \
  {                                                                            \
    if (e) {                                                                   \
      cout << SDL_GetError() << endl;                                          \
      SDL_Quit();                                                              \
      return -1;                                                               \
    }                                                                          \
  }

int x_player = 200;
int y_player = 200;
int velocity = 1;

int main(int , char **) {
  using namespace std;
  using namespace std::chrono;
  const int width = 500;
  const int height = 500;

  errcheck(SDL_Init(SDL_INIT_VIDEO) != 0);

  SDL_Window *window = SDL_CreateWindow(
      "My Next Superawesome Game", SDL_WINDOWPOS_UNDEFINED,
      SDL_WINDOWPOS_UNDEFINED, width, height, SDL_WINDOW_SHOWN);
  errcheck(window == nullptr);

  SDL_Renderer *renderer = SDL_CreateRenderer(
      window, -1, SDL_RENDERER_ACCELERATED);
  errcheck(renderer == nullptr);

  int textureWidth = 627;
  int textureHeight = 663;
  SDL_Texture* objectTexture = nullptr;
  objectTexture = IMG_LoadTexture(renderer, "../data/ShipsPNG/ship2.png");
  SDL_QueryTexture(objectTexture, NULL, NULL, &textureWidth, &textureHeight);



    //auto dt = 15ms;
  milliseconds dt(15);

  steady_clock::time_point current_time = steady_clock::now(); // remember current time
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
          y_player-=velocity;
      } else if (keyboardState[SDL_SCANCODE_S]) {
          y_player+=velocity;
      } else if (keyboardState[SDL_SCANCODE_A]) {
          x_player-=velocity;
      } else if (keyboardState[SDL_SCANCODE_D]) {
          x_player+=velocity;
      } else {

      }

    SDL_SetRenderDrawColor(renderer, 255, 255, 0, 255);
    SDL_Rect kwadrat = {x_player, y_player, 10, 10};
    SDL_RenderFillRect(renderer, &kwadrat);


    SDL_RenderPresent(renderer); // draw frame to screen

    this_thread::sleep_until(current_time = current_time + dt);
  }
  SDL_DestroyRenderer(renderer);
  SDL_DestroyWindow(window);
  SDL_Quit();
  return 0;
}
