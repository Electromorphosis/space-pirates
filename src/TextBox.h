//
// Created by mechlon on 23.06.24.
//

#ifndef SPACE_PIRATES_TEXTBOX_H
#define SPACE_PIRATES_TEXTBOX_H
#include "Window.h"
#include <SDL2/SDL_image.h>
#include <SDL2/SDL_ttf.h>

#include <string>
class Window;

class TextBox {
public:
    Window* window;
    SDL_Texture* textTexture = nullptr;
    SDL_Surface* surfaceMessage = nullptr;
    TTF_Font* Sans = TTF_OpenFont("data/font/Audiowide-Regular.ttf", 20);
    SDL_Color White = {255, 255, 255, 0};
    TextBox(Window* _window, int posX, int posY, int width, int height, std::string content);
    TextBox(Window* _window, int posX, int posY, int width, int height, std::string content, int fontSize);
    void Render(Window &window);

    int posX;
    int posY;
    int width;
    int height;
    std::string content;
};


#endif //SPACE_PIRATES_TEXTBOX_H
