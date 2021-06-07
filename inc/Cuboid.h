#pragma once

#include "Polygon.h"

const int WALLS = 6;

class Cuboid : public Object {
private:
    std::array<Polygon<RECTANGLE>, WALLS> walls;

    void calculateCenterOfSymmetry();
public:
    Cuboid() = default;

    Cuboid(double width, double height, double lenght, std::string _color = DEFAULT_COLOR);

    Cuboid(Vector<STANDARD_SIZE> v, Vector<STANDARD_SIZE> r, Vector<STANDARD_SIZE> w, std::string _color = DEFAULT_COLOR);

    Cuboid(std::array<Vector<STANDARD_SIZE>, 8> points);

    void draw() override;

    void translation(Vector<STANDARD_SIZE> translationVector) override;

    void translation(double x, double y, double z);

    void rotationMain(Vector<STANDARD_SIZE> rotations) override;

    void rotationMain(double x, double y, double z);

    void rotationLocal(Vector<STANDARD_SIZE> rotations) override;

    void rotationLocal(double x, double y, double z);

    void setColor(std::string _color) override;

    const Polygon<RECTANGLE> & operator[](int index) const;

    Polygon<RECTANGLE> & operator[](int index);
};