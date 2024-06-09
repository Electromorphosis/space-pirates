//
// Created by mechlon on 09.06.24.
//

#include "TextureData.h"

TextureData::TextureData() {

}

TextureData::TextureData(std::string textureName, int width, int height, std::string path) {
    name = textureName;
    textureWidth = width;
    textureHeight = height;
    textureFilepath = path;

}