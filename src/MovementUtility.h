
#ifndef SPACE_PIRATES_MOVEMENTVECTOR_H
#define SPACE_PIRATES_MOVEMENTVECTOR_H

#include <vector>

#include <SDL2/SDL.h>

class MovementUtility {
public:
    std::vector<float> calculate(int angle) {
        //              [0,1]
        //                |
        //           IV   |  I
        //  [-1,0]----------------[1,0]
        //           III  |  II
        //                |
        //              [0,-1]

        // In square braces there are pure or cardinal vectors; values between them need to be calculated proportionally
        // and then attempted to be recalculated into actual pixel movement which - obviously - cannot be by nothing else
        // but a natural number of pixels. Basically a kind of a re-implementation of rasterization algo.
        angle %= 360; // Trim angle if needed
        if (angle < 0) {
            angle += 360; // -180 becomes 180, -270 becomes 90, -90 becomes 270 etc.
        }

        // SDL_Log("Angle: %i", angle);

        float vectorX = 0;
        float vectorY = 0;
        float tilt;

        if (angle >= 0 && angle < 90) { // First quarter, i.e. up-right
            tilt = (float)angle / 90;
            vectorX = tilt;
            vectorY = 1 - tilt;
        } else if (angle >= 90 && angle < 180) {// Second quarter, right-down
            tilt = ((float)angle - 90) / 90;
            vectorX = 1 - tilt;
            vectorY = -tilt;
        } else if (angle >= 180 && angle < 270) { // etc.
            tilt = ((float)angle - 180) / 90;
            vectorX = -tilt;
            vectorY = -(1 - tilt);
        } else {
            tilt = ((float)angle - 270) / 90;
            vectorX = -1 + tilt;
            vectorY = tilt;
        }
        // SDL_Log("Tilt: %f", tilt);
        std::vector<float> result;
        result.push_back(vectorX);
        result.push_back(vectorY);
        return result;
    };

};

#endif //SPACE_PIRATES_MOVEMENTVECTOR_H
