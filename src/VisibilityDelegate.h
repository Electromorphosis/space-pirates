//
// Created by mechlon on 06.06.24.
//

#ifndef SPACE_PIRATES_VISIBILITYDELEGATE_H
#define SPACE_PIRATES_VISIBILITYDELEGATE_H

#include <string>
#include <iostream>

#include "TextureData.h"

class VisibilityDelegate
{
public:
    TextureData* textureData;
    SDL_Texture* objectTexture;
    SDL_Renderer* sdlRenderer;

    virtual void draw(SDL_Renderer* renderer) = 0;
};

class NotVisible : public VisibilityDelegate
{
public:
    NotVisible() : VisibilityDelegate() {}

    void draw(SDL_Renderer* renderer) override {
        // no-op
    };

};

class Visible : public VisibilityDelegate
{
public:
    explicit Visible(SDL_Renderer* sdlRenderer, TextureData *textureDataProvided) : VisibilityDelegate() {
        this->textureData = textureDataProvided;
        objectTexture = IMG_LoadTexture(sdlRenderer, textureDataProvided->textureFilepath.c_str());
        if (SDL_QueryTexture(objectTexture, nullptr, nullptr,  &textureData->textureWidth, &textureData->textureHeight) == -1) {
            std::cout << "(SDL) Error when loading texture on filepath:" << textureData->textureFilepath << std::endl;
        };
    };
    void draw(SDL_Renderer* renderer) override {
    // Actual draw logic
    };


};


#endif //SPACE_PIRATES_VISIBILITYDELEGATE_H
