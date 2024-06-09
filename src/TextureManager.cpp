//
// Created by mechlon on 08.06.24.
//

#include <string>
#include <SDL2/SDL.h>
#include "TextureManager.h"

TextureManager::TextureManager() {
    playerTexture = new TextureData();
    textureDataRootPath = "../data/";
    playerTextureWidth = 32;
    playerTexture->name = "Player";
    playerTexture->textureFilepath = textureDataRootPath + std::string("ShipsPNG/ship0.png");

    playerTexture->textureWidth = playerTextureWidth;
    playerTexture->textureHeight = playerTextureWidth;
    textureDataVector.push_back(playerTexture);

}

TextureData* TextureManager::getTextureByName(std::string name) {
    for (TextureData* data : textureDataVector) {
        std::string thisName = data->name;
        SDL_Log("Extracted texture data of name: %s", thisName.c_str());

        if (data->name == name) {
            return data; // Casting the pointer acceptable, bc TextureDataVector is ought to be Read-only
        }
    }
    SDL_Log("Warning! Texture was not found. Null pointer will be returned!");
    return nullptr; // Texture not found
}

TextureManager::~TextureManager() {}