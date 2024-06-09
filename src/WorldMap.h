//
// Created by mechlon on 08.06.24.
//

#ifndef SPACE_PIRATES_WORLDMAP_H
#define SPACE_PIRATES_WORLDMAP_H

#include <vector>
#include "GameObject.h"
#include "Player.h"

class WorldMap {
public:
    struct MappedObject{
        MappedObject(GameObject* gameObject, int initX, int initY){
            mappedGameObject = gameObject;
            x = initX;
            y = initY;
        }

        int x;
        int y;
        GameObject* mappedGameObject;
    };

    WorldMap();
    ~WorldMap();

    std::vector<MappedObject*> getAllGameObjects();
//    std::vector<MappedObject*> calculateVisibleGameObjects(Player* player);

private:
    std::vector<MappedObject*> globalGameObjects;

};


#endif //SPACE_PIRATES_WORLDMAP_H
