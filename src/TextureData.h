//
// Created by mechlon on 08.06.24.
//

#ifndef SPACE_PIRATES_TEXTUREDATA_H
#define SPACE_PIRATES_TEXTUREDATA_H

struct TextureData {
    TextureData(std::string textureName, int width, int height, std::string path){
        name = textureName;
        textureWidth = &width;
        textureHeight = &height;
        textureFilepath = path;
    }
    std::string name;
    int *textureWidth;
    int *textureHeight;
    std::string textureFilepath;
};
#endif //SPACE_PIRATES_TEXTUREDATA_H
