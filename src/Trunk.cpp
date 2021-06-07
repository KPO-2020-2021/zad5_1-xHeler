#include "Trunk.h"

Trunk::Trunk(double _scale, double lenght, double height) {
    lenght = lenght * _scale;
    height = height * _scale;
    createMainWalls(lenght, height);
    createOtherWalls();
    centerOfSymmetry = Vector();
    setColor(DEFAULT_COLOR);
}

void Trunk::createMainWalls(double lenght, double height) {
    double triangleParametr = 0.2;
    std::array<Vector<STANDARD_SIZE>, 4> points;

    points[0] = Vector<3>({-(lenght / 2), -(height / 2), 0});
    points[1] = Vector<3>({(lenght / 2), -(height / 2), 0});
    points[2] = Vector<3>({(lenght / 2) + triangleParametr * lenght, (height / 2), 0});
    points[3] = Vector<3>({-(lenght / 2), (height / 2), 0});

    Polygon<4> rect(points);
    rect.translation(0, 0, height / 2);
    walls.emplace_back(rect);
    rect.translation(0, 0, -height);
    walls.emplace_back(rect);

}
void Trunk::createOtherWalls() {
    Polygon down({walls[0][0], walls[0][1], walls[1][1], walls[1][0]});
    Polygon up({walls[0][3], walls[0][2], walls[1][2], walls[1][3]});
    Polygon back({walls[0][0], walls[1][0], walls[1][3], walls[0][3]});
    Polygon front({walls[0][1], walls[1][1], walls[1][2], walls[0][2]});
    
    walls.emplace_back(std::move(down));
    walls.emplace_back(std::move(up));
    walls.emplace_back(std::move(back));
    walls.emplace_back(std::move(front));
}

void Trunk::draw() {
    for (int i = 0; i < walls.size(); ++i) {
        walls[i].draw();
    }
}

void Trunk::translation(Vector<STANDARD_SIZE> translationVector) {
    centerOfSymmetry = centerOfSymmetry + translationVector;
    for (int i = 0; i < walls.size(); ++i) {
        walls[i].translation(translationVector);
    }
}

void Trunk::translation(double x, double y, double z) {
    translation(Vector<STANDARD_SIZE>({x, y, z}));
}

void Trunk::rotationMain(Vector<STANDARD_SIZE> rotations) {
    centerOfSymmetry.rotateByEulerAngles(rotations[0], rotations[1], rotations[2]);
    for (int i = 0; i < walls.size(); ++i) {
        walls[i].rotationMain(rotations);
    }
}

void Trunk::rotationLocal(Vector<STANDARD_SIZE> rotations) {
    Vector tmp = centerOfSymmetry * -1;
    translation(tmp);
    rotationMain(rotations);
    tmp = tmp * -1;
    translation(tmp);
    centerOfSymmetry = tmp;
}

void Trunk::setColor(std::string _color) {
    color = _color;
    for (int i = 0; i < walls.size(); ++i) {
        walls[i].setColor(color);
    }
}

Vector<STANDARD_SIZE> Trunk::getCenterOfSymmetry() {
    return centerOfSymmetry;
}

