#pragma once

#include "Matrix.h"
#include <iostream>

const int PRECISION = 10;
const int MATRIX_SIZE = 3;
const int COEFFICIENTS_NUMBERS = 4;

class Quaternion {
private:
    double W;
    double X;
    double Y;
    double Z;

public:
    Quaternion();

    Quaternion(double w, double x, double y, double z);

    Matrix<MATRIX_SIZE> getRotationMatrix();

    friend std::ostream &operator<<(std::ostream &ost, const Quaternion &qua);

    Quaternion operator+(const Quaternion &q);

    Quaternion operator*(const Quaternion &q);

    bool operator==(const Quaternion &q) const;

    void conjugate();

    Quaternion getConjugate();

    const double operator[](int index) const;

    double &operator[](int index);
};

std::ostream &operator<<(std::ostream &ost, const Quaternion &qua);

std::istream &operator>>(std::istream &ist, Quaternion &qua);
