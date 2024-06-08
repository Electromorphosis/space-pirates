//
// Created by mechlon on 08.06.24.
//

#include <vector>
#include "WorldMap.h"
#include "Player.h"
#include "GlobalSettings.h"


WorldMap::WorldMap() {}

WorldMap::~WorldMap() {
    if(!globalGameObjects.empty()) {
        for(const std::vector<MappedObject*>& currentGameObject : globalGameObjects ) {
        delete currentGameObject;
        }
    }
    delete globalGameObjects;
}


std::vector<WorldMap::MappedObject*> WorldMap::getAllGameObjects() {
    return globalGameObjects;
}

//
//public std::vector<MappedObject*> WorldMap::calculateVisibleGameObjects(Player* player) {
//    int playerX = player.getPlayerX;
//    int playerY = player.getPlayerY;
//    int screenWidth = GlobalSettings.get
//    std::vector<MappedObject*> visibleGameObjects;
//    for(const std::vector<MappedObject*>& currentGameObject : globalGameObjects ) {
//        int currentObjectX = currentGameObject. // tba
//        if
//    }
//}
