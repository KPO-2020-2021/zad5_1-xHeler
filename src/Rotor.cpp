#include "Rotor.h"

Rotor::Rotor(double radius) {
    setupPropellers(radius);
    centerOfSymmetry = Vector();
    setColor(DEFAULT_COLOR);
}

void Rotor::draw() {
    for (int i = 0; i < PROPELLER; ++i) {
        propellers[i].draw();
    }
}

void Rotor::translation(Vector<STANDARD_SIZE> translationVector) {
    centerOfSymmetry = centerOfSymmetry + translationVector;
    for (int i = 0; i < PROPELLER; ++i) {
        propellers[i].translation(translationVector);
    }
}

void Rotor::rotationMain(Vector<STANDARD_SIZE> rotations) {
    centerOfSymmetry.rotateByEulerAngles(rotations[0], rotations[1], rotations[2]);
    for (int i = 0; i < PROPELLER; ++i) {
        propellers[i].rotationMain(rotations);
    }
}

void Rotor::rotationLocal(Vector<STANDARD_SIZE> rotations) {
    Vector tmp = centerOfSymmetry * -1;
    translation(tmp);
    rotationMain(rotations);
    tmp = tmp * -1;
    translation(tmp);
    centerOfSymmetry = tmp;
}

void Rotor::setColor(std::string _color) {
    color = _color;
    for (int i = 0; i < PROPELLER; ++i) {
        propellers[i].setColor(color);
    }
}

void Rotor::setupPropellers(double radius) {
    propellers[0] = Cuboid(2 * radius- 0.05 * radius * 2, 1, 3);
    propellers[0].rotationMain(45, 0, 0);
    propellers[1] = propellers[0];
    propellers[1].rotationMain(0, 90, 0);
}
