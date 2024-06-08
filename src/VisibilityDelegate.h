//
// Created by mechlon on 06.06.24.
//

#ifndef SPACE_PIRATES_VISIBILITYDELEGATE_H
#define SPACE_PIRATES_VISIBILITYDELEGATE_H


class VisibilityDelegate
{
public:
    virtual void draw() = 0;
};

class NotVisible : public VisibilityDelegate
{
public:
    virtual void draw() override {
        // no-op
    }
};

class Visible : public VisibilityDelegate
{
public:
    virtual void draw() override {
        // code to draw a model at the position of this object
    }
};


#endif //SPACE_PIRATES_VISIBILITYDELEGATE_H
