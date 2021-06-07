#pragma once

#include "Cuboid.h"

const int PROPELLER = 2;
const double RADIUS = 30;

class Rotor : public Object {
private:
    std::array<Cuboid, PROPELLER> propellers;

    void setupPropellers(double radius);
public:
    Rotor(double radius = RADIUS);

    void rotationPropellers(double velocity);

    void draw() override;

    void translation(Vector<STANDARD_SIZE> translationVector) override;

    void rotationMain(Vector<STANDARD_SIZE> rotations) override;

    void rotationLocal(Vector<STANDARD_SIZE> rotations) override;

    void setColor(std::string _color) override;
};
