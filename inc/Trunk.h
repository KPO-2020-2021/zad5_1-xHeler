#pragma once

#include "Polygon.h"

const double LENGHT = 75;
const double HEIGHT = 25;

class Trunk : public Object {
private:
    std::vector<Polygon<RECTANGLE>> walls;

    void createMainWalls(double lenght, double height);

    void createOtherWalls();

public:
    Trunk(double _scale = 1, double lenght = LENGHT, double height = HEIGHT);

    void draw() override;

    void translation(Vector<STANDARD_SIZE> translationVector) override;

    void translation(double x, double y, double z);

    void rotationMain(Vector<STANDARD_SIZE> rotations) override;

    void rotationLocal(Vector<STANDARD_SIZE> rotations) override;

    void setColor(std::string _color) override;

    Vector<STANDARD_SIZE> getCenterOfSymmetry() override;
};