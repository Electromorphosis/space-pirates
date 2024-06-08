//
// Created by mechlon on 08.06.24.
//

#ifndef SPACE_PIRATES_TEXTUREMANAGER_H
#define SPACE_PIRATES_TEXTUREMANAGER_H

#include "TextureData.h"

#include <vector>
#include <string>

class TextureManager {
public:
    TextureManager();
    ~TextureManager();

    TextureData* getTextureByName(std::string name);

private:
    std::vector<TextureData*> textureDataVector;
};


#endif //SPACE_PIRATES_TEXTUREMANAGER_H
