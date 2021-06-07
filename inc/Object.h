#pragma once

#include "Vector.h"

const std::string DEFAULT_COLOR = "#000000";

class Object {
protected:
    std::string color;
    Vector<STANDARD_SIZE> centerOfSymmetry;
public:
    virtual void draw() {}

    virtual void translation(Vector<STANDARD_SIZE> translationVector){}

    virtual void rotationMain(Vector<STANDARD_SIZE> rotations){}

    virtual void rotationLocal(Vector<STANDARD_SIZE> rotations){}

    virtual void setColor(std::string _color){color = _color;}

    virtual Vector<STANDARD_SIZE> getCenterOfSymmetry() { return centerOfSymmetry;}

};