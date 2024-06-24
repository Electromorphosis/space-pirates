
#ifndef SPACE_PIRATES_TEXTBOX_H
#define SPACE_PIRATES_TEXTBOX_H

#include <string>

#include <SDL2/SDL_image.h>
#include <SDL2/SDL_ttf.h>

#include "Window.h"

class Window;

class TextBox {
public:
    TextBox(Window* _window, int posX, int posY, int width, int height, std::string content);
    TextBox(Window* _window, int posX, int posY, int width, int height, std::string content, int fontSize);

    void Render(Window &window);

    TTF_Font* Sans = TTF_OpenFont("data/font/Audiowide-Regular.ttf", 20);
    SDL_Color White = {255, 255, 255, 0};
    SDL_Texture* textTexture = nullptr;
    SDL_Surface* surfaceMessage = nullptr;
    Window* window;
    std::string content;

    int posX;
    int posY;
    int width;
    int height;
};

#endif //SPACE_PIRATES_TEXTBOX_H
