//
// Created by mechlon on 06.06.24.
//

#ifndef SPACE_PIRATES_UPDATE_H
#define SPACE_PIRATES_UPDATE_H

#include <string>

class UpdateDelegate
{
public:
    const bool Movable = false;
    virtual void update() = 0;
    operator std::string() const { return "1"; }
};

class NotMovable : public UpdateDelegate
{
public:
    virtual void update() override {
        // no-op
    }
    const bool Movable = false;
};

class Movable : public UpdateDelegate
{
public:
    const bool Movable = true;
    virtual void update() override {
        // code to update the position of this object
    }

    float velocityX;
    float velocityY;
};

#endif //SPACE_PIRATES_UPDATE_H
