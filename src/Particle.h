
#ifndef SPACE_PIRATES_PARTICLE_H
#define SPACE_PIRATES_PARTICLE_H

#include <string>

#include "Window.h"
#include "GameObject.h"

class Particle : public GameObject {
public:
    Particle(Window* _window);
    Particle(Window* _window, float posX, float posY, int dispersionRate, std::string spawn, bool randCol);
    ~Particle();

    void Render(Window &renderer) override;
    void Damage(int dp) override;

    Window* window;

    int textureWidth = 2;
    int textureHeight = 2;
    float positionX = 0;
    float positionY = 0;
    int angle = 0;
    int ttl = 5; // Time To Live default value - eventually could also be changed
    int testStartPosX =0;
    int testStartPosY =0;
};

#endif //SPACE_PIRATES_ROCK_H
