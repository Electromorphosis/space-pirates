//
// Created by mechlon on 09.06.24.
//

#ifndef SPACE_PIRATES_ROCK_H
#define SPACE_PIRATES_ROCK_H
#include "GameObject.h"
#include <string>
#include "CollisionBox.h"
#include "CollisionType.h"
#include "GlobalEventHandler.h"

class Rock : public GameObject {
public:
    Rock(Window* _window, GlobalEventHandler* _events);
    Rock(Window* _window, GlobalEventHandler* _events, std::string spawn);
    Rock(Window* _window, GlobalEventHandler* _events, int face, int angle, int spawnPoint, const std::string& spawn);
    ~Rock();
    Window* window;
    GlobalEventHandler* geh;
    int textureWidth = 32;
    int textureHeight = 32;
//    CollisionBox collisionBox = CollisionBox(nullptr, 0, 0, 0, 0, CollisionType::TerrainDestructible);
    void Render(Window &renderer) override;
    void Damage(int dp) override;
};


#endif //SPACE_PIRATES_ROCK_H
