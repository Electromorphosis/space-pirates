//
// Created by mechlon on 08.06.24.
//

#include "TextureManager.h"
#include "TextureData.h"

TextureManager::TextureManager() {
    TextureData playerTexture = TextureData();
    std::string textureDataRootPath = "../data/";
    playerTexture.name = "Player";
    playerTexture.textureFilepath = textureDataRootPath + "ShipsPNG/ship0.png";
    int playerTextureWidth = 32;
    playerTexture.textureWidth = &playerTextureWidth;
    playerTexture.textureHeight = &playerTextureWidth;

}