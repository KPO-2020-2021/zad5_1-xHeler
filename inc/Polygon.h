#pragma once

#include "Gnuplot.h"
#include "Vector.h"
#include "Object.h"

inline Gnuplot plot;
const int DEFAULT_RADIUS = 30;
const int HEXAGON = 6;
const int RECTANGLE = 4;
const int TRIANGLE = 3;
const int LINE = 2;

template<int SIZE = RECTANGLE>
class Polygon : public Object {
private:
    std::string id;

    std::array<Vector<STANDARD_SIZE>, SIZE> points;

    void createPolygon(double radius, char axis = 'x');

    void setId();

public:
    explicit Polygon(char axis = 'x');

    explicit Polygon(double radius, char axis = 'x', std::string _color = DEFAULT_COLOR);

    explicit Polygon(std::array<Vector<STANDARD_SIZE>, SIZE> args) : points(args) {color = DEFAULT_COLOR;}

    Polygon(Vector<STANDARD_SIZE> v, Vector<STANDARD_SIZE> w, Vector<STANDARD_SIZE> translationVector,
            std::string _color = DEFAULT_COLOR);

    void draw() override;

    void translation(Vector<STANDARD_SIZE> translationVector) override;

    void translation(double x, double y, double z);

    void rotationMain(Vector<STANDARD_SIZE> rotations) override;

    void rotationMain(double x, double y, double z);

    void rotationLocal(Vector<STANDARD_SIZE> rotations) override;

    void rotationLocal(double x, double y, double z);

    void setColor(std::string color) override;

    const Vector<STANDARD_SIZE> &operator[](int index) const;

    Vector<STANDARD_SIZE> &operator[](int index);
};

template<int SIZE>
Polygon<SIZE>::Polygon(char axis) {
    double radius = DEFAULT_RADIUS;
    color = DEFAULT_COLOR;
    createPolygon(radius, axis);
    centerOfSymmetry = Vector<STANDARD_SIZE>();
    setColor(color);
}


template<int SIZE>
Polygon<SIZE>::Polygon(double radius, char axis, std::string _color) {
    color = _color;
    createPolygon(radius, axis);
    centerOfSymmetry = Vector<STANDARD_SIZE>();
    setColor(color);
}

//template<int SIZE>
//Polygon<SIZE>::Polygon(Vector<STANDARD_SIZE> v, Vector<STANDARD_SIZE> w, std::string _color) {
//    points[0] = Vector({0, 0, 0});
//    points[1] = v;
//    points[2] = v + w;
//    points[3] = w;
//    color = _color;
//    double x = distanceBetweenTwoVectors(points[0], points[1]);
//    double y = distanceBetweenTwoVectors(points[3], points[0]);
//    double z = distanceBetweenTwoVectors(points[2], points[0]);
//    centerOfSymmetry = Vector<STANDARD_SIZE>({x, y, z});
//    setColor(color);
//}

template<int SIZE>
Polygon<SIZE>::Polygon(Vector<STANDARD_SIZE> v, Vector<STANDARD_SIZE> w, Vector<STANDARD_SIZE> translationVector,
                       std::string _color) {
    points[0] = Vector({0, 0, 0});
    points[1] = v;
    points[2] = v + w;
    points[3] = w;
    color = _color;
    double x = distanceBetweenTwoVectors(points[0], points[1]);
    double y = distanceBetweenTwoVectors(points[3], points[0]);
    double z = distanceBetweenTwoVectors(points[2], points[0]);
    centerOfSymmetry = Vector<STANDARD_SIZE>({x, y, z});
    setColor(color);
    translation(translationVector);
}


template<int SIZE>
void Polygon<SIZE>::createPolygon(double radius, char axis) {
    double degree = 360;
    Vector tmp({0, 0, 0});
    switch (axis) {
        case 'x':
            tmp[0] = radius;
            for (int i = 0; i < SIZE; ++i) {
                points[i] = tmp;
                tmp.rotateByEulerAngles(0, degree / SIZE, 0);
            }
            break;
        case 'y':
            tmp[1] = radius;
            for (int i = 0; i < SIZE; ++i) {
                points[i] = tmp;
                tmp.rotateByEulerAngles(0, 0, degree / SIZE);
            }
            break;
        case 'z':
            tmp[2] = radius;
            for (int i = 0; i < SIZE; ++i) {
                points[i] = tmp;
                tmp.rotateByEulerAngles(degree / SIZE, 0, 0);
            }
            break;
        default:
            break;
    }
}

template<int SIZE>
void Polygon<SIZE>::setId() {
    if (id.empty()) {
        id = "P#" + std::to_string(listOfObject.size() + 1);
    }
}

template<int SIZE>
void Polygon<SIZE>::draw() {
    std::stringstream tmp, command;
    setId();
    tmp << "from " << points[0][0] << "," << points[0][2] << "," << points[0][1] << " to ";
    for (int i = 1; i < SIZE; ++i) {
        tmp << points[i][0] << "," << points[i][2] << "," << points[i][1] << " to ";
    }
    tmp << points[0][0] << "," << points[0][2] << "," << points[0][1];

    if (listOfObject.find(id) == listOfObject.end()) {
        listOfObject[id] = listOfObject.size() + 1;
    }
    command << "set object " << listOfObject[id] << " polygon " << tmp.str() <<
            " fillstyle transparent solid fillcolor rgb \"" << color << "\"";

    plot.sendcommand(command.str());
}

template<int SIZE>
void Polygon<SIZE>::translation(Vector<STANDARD_SIZE> translationVector) {
    for (int i = 0; i < SIZE; ++i) {
        points[i].translation(translationVector);
    }
}

template<int SIZE>
void Polygon<SIZE>::translation(double x, double y, double z) {
    translation(Vector<STANDARD_SIZE>({x, y, z}));
}

template<int SIZE>
void Polygon<SIZE>::rotationMain(Vector<STANDARD_SIZE> rotations) {
    for (int i = 0; i < SIZE; ++i) {
        points[i].rotateByEulerAngles(rotations[0], rotations[1], rotations[2]);
    }
}

template<int SIZE>
void Polygon<SIZE>::rotationMain(double x, double y, double z) {
    rotationMain(Vector<STANDARD_SIZE>({x, y, z}));
}

template<int SIZE>
void Polygon<SIZE>::rotationLocal(Vector<STANDARD_SIZE> rotations) {
    Vector<STANDARD_SIZE> tmp = centerOfSymmetry * -1;
    translation(tmp);
    rotationMain(rotations);
    translation(tmp * -1);
}

template<int SIZE>
void Polygon<SIZE>::rotationLocal(double x, double y, double z) {
    rotationLocal(Vector<STANDARD_SIZE>({x, y, z}));
}

template<int SIZE>
void Polygon<SIZE>::setColor(std::string _color) {
    if (_color.length() != 7 || _color[0] != '#') throw std::invalid_argument("Unknow rgb format!");
    color = _color;
}

template<int SIZE>
const Vector<STANDARD_SIZE> &Polygon<SIZE>::operator[](int index) const {
    if (index >= SIZE || index < 0) throw std::invalid_argument("Index out of range!");
    return points[index];
}

template<int SIZE>
Vector<STANDARD_SIZE> &Polygon<SIZE>::operator[](int index) {
    if (index >= SIZE || index < 0) throw std::invalid_argument("Index out of range!");
    return points[index];
}



