
#include <SDL2/SDL.h>
#include <SDL2/SDL_ttf.h>

#include "TextBox.h"

TextBox::TextBox(Window *_window, int x, int y, int w, int h, std::string c, int fontSize) {
    window = _window;
    posX = x;
    posY = y;
    width = w;
    height = h;
    content = c;
    Sans = TTF_OpenFont("data/font/Audiowide-Regular.ttf", fontSize);

}

TextBox::TextBox(Window* _window, int x, int y, int w, int h, std::string c) {
    window = _window;
    posX = x;
    posY = y;
    width = w;
    height = h;
    content = c;
}

void TextBox::Render(Window &window) {
    surfaceMessage = TTF_RenderText_Solid(Sans, content.c_str(), White);
    textTexture = SDL_CreateTextureFromSurface(window.renderer, surfaceMessage);

    SDL_Rect Message_rect;
    Message_rect.x = posX;
    Message_rect.y = posY;
    Message_rect.w = width;
    Message_rect.h = height;
    SDL_Rect srcRect = { 0 , 0, width, height };;
    SDL_RenderCopy(window.renderer, textTexture, &srcRect, &Message_rect);
}
