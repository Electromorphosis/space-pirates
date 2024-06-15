//
// Created by mechlon on 15.06.24.
//

#ifndef SPACE_PIRATES_LASERBEAM_H
#define SPACE_PIRATES_LASERBEAM_H
#include "GameObject.h"

class LaserBeam : public GameObject {
public:
    LaserBeam(Window* _window, float posX, float posY, int angle);
    ~LaserBeam();
    Window* window;
    int textureWidth = 9;
    int textureHeight = 9;

    void Render(Window &renderer) override;


};


#endif //SPACE_PIRATES_LASERBEAM_H
