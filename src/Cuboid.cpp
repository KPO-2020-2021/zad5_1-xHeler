#include "Cuboid.h"

Cuboid::Cuboid(double width, double height, double lenght, std::string _color) {
    color = _color;
    Vector v ({width, 0, 0});
    Vector r ({0, height, 0});
    Vector w ({0, 0, lenght});

    walls[0] = Polygon(v, w, Vector());
    walls[1] = Polygon(w, v, r);
    walls[2] = Polygon(r, w, Vector());
    walls[3] = Polygon(r, v, w);
    walls[4] = Polygon(r, w, v);
    walls[5] = Polygon(r, v, Vector());

    calculateCenterOfSymmetry();
    setColor(color);

    Vector tmp = centerOfSymmetry * -1;
    translation(tmp);
}

Cuboid::Cuboid(Vector<STANDARD_SIZE> v, Vector<STANDARD_SIZE> r, Vector<STANDARD_SIZE> w, std::string _color) {
    color = _color;
    walls[0] = Polygon(v, w, Vector());
    walls[1] = Polygon(w, v, r);
    walls[2] = Polygon(r, w, Vector());
    walls[3] = Polygon(r, v, w);
    walls[4] = Polygon(r, w, v);
    walls[5] = Polygon(r, v, Vector());

    calculateCenterOfSymmetry();
    setColor(color);

    Vector tmp = centerOfSymmetry * -1;
    translation(tmp);
}

Cuboid::Cuboid(std::array<Vector<STANDARD_SIZE>, 8> points) {
    color = DEFAULT_COLOR;
    walls[0] = Polygon({points[0], points[1], points[2], points[3]});
    walls[1] = Polygon({points[4], points[5], points[6], points[7]});
    walls[2] = Polygon({points[4], points[0], points[1], points[5]});
    walls[3] = Polygon({points[5], points[1], points[2], points[6]});
    walls[4] = Polygon({points[7], points[3], points[2], points[6]});
    walls[5] = Polygon({points[4], points[0], points[3], points[7]});
    calculateCenterOfSymmetry();
    setColor(color);

    Vector tmp = centerOfSymmetry * -1;
    translation(tmp);
}

void Cuboid::draw() {
    for (int i = 0; i < WALLS; ++i) {
        walls[i].draw();
    }
}

void Cuboid::translation(Vector<STANDARD_SIZE> translationVector) {
    for (int i = 0; i < WALLS; ++i) {
        walls[i].translation(translationVector);
    }
}

void Cuboid::translation(double x, double y, double z) {
    translation(Vector({x, y, z}));
}

void Cuboid::rotationMain(Vector<STANDARD_SIZE> rotations) {
    for (int i = 0; i < WALLS; ++i) {
        walls[i].rotationMain(rotations);
    }
}

void Cuboid::rotationMain(double x, double y, double z) {
    rotationMain(Vector({x, y, z}));;
}

void Cuboid::rotationLocal(Vector<STANDARD_SIZE> rotations) {
    Vector tmp = centerOfSymmetry * -1;
    translation(tmp);
    rotationMain(rotations);
    translation(tmp * -1);
}

void Cuboid::rotationLocal(double x, double y, double z) {
    rotationLocal(Vector({x, y, z}));
}

void Cuboid::setColor(std::string _color) {
    if (_color.length() != 7 || _color[0] != '#') throw std::invalid_argument("Unknow rgb format!");
    color = _color;
    for (int i = 0; i < WALLS; ++i) {
        walls[i].setColor(color);
    }
}

const Polygon<RECTANGLE> &Cuboid::operator[](int index) const {
    if (index >= WALLS || index < 0) throw std::invalid_argument("Index out of range!");
    return walls[index];
}

Polygon<RECTANGLE> &Cuboid::operator[](int index) {
    if (index >= WALLS || index < 0) throw std::invalid_argument("Index out of range!");
    return walls[index];
}

void Cuboid::calculateCenterOfSymmetry() {
    double x = distanceBetweenTwoVectors(walls[0][0], walls[0][3]) / 2;
    double y = distanceBetweenTwoVectors(walls[0][0], walls[1][0]) / 2;
    double z = distanceBetweenTwoVectors(walls[0][0], walls[0][1]) / 2;
    centerOfSymmetry = Vector({z, y, x});
}
