#include <iomanip>
#include "Quaternion.h"

Quaternion::Quaternion() {
    this->W = 1;
    this->X = 0;
    this->Y = 0;
    this->Z = 0;
}

Quaternion::Quaternion(double w, double x, double y, double z) {
    this->W = w;
    this->X = x;
    this->Y = y;
    this->Z = z;
}

Matrix<MATRIX_SIZE> Quaternion::getRotationMatrix() {
    double A = 1 - 2 * Y * Y - 2 * Z * Z;
    double B = 2 * X * Y - 2 * Z * W;
    double C = 2 * X * Z + 2 * Y * W;
    double D = 2 * X * Y + 2 * Z * W;
    double E = 1 - 2 * X * X - 2 * Z * Z;
    double F = 2 * Y * Z - 2 * X * W;
    double G = 2 * X * Z - 2 * Y * W;
    double H = 2 * Y * Z + 2 * X * W;
    double I = 1 - 2 * X * X - 2 * Y * Y;
    return Matrix<MATRIX_SIZE>({A, B, C, D, E, F, G, H, I});
}

Quaternion Quaternion::operator+(const Quaternion &v) {
    return Quaternion(W + v[0], X + v[1], Y + v[2], Z + v[3]);
}

std::ostream &operator<<(std::ostream &ost, const Quaternion &qua) {
    std::cout << std::fixed;
    std::cout << std::setprecision(PRECISION);
    ost << qua[0] << ",";
    ost << qua[1] << ",";
    ost << qua[2] << ",";
    ost << qua[3];

    return ost;
}

Quaternion Quaternion::operator*(const Quaternion &q) {
    return Quaternion(W * q.W - X * q.X - Y * q.Y - Z * q.Z,
                      W * q.X + X * q.W + Y * q.Z - Z * q.Y,
                      W * q.Y - X * q.Z + Y * q.W + Z * q.X,
                      W * q.Z + X * q.Y - Y * q.X + Z * q.W);
}

void Quaternion::conjugate() {
    X = -X;
    Y = -Y;
    Z = -Z;
}

Quaternion Quaternion::getConjugate() {
    Quaternion tmp(W, X, Y, Z);
    tmp.conjugate();
    return tmp;
}

double &Quaternion::operator[](int index) {
    if (index >= COEFFICIENTS_NUMBERS || index < 0) throw std::invalid_argument("Index out of range!");
    switch (index) {
        case 0:
            return W;
        case 1:
            return X;
        case 2:
            return Y;
        case 3:
            return Z;
        default:
            throw std::exception();
    }
}

const double Quaternion::operator[](int index) const {
    if (index >= COEFFICIENTS_NUMBERS || index < 0) throw std::invalid_argument("Index out of range!");
    switch (index) {
        case 0:
            return W;
        case 1:
            return X;
        case 2:
            return Y;
        case 3:
            return Z;
        default:
            throw std::exception();
    }
}

bool Quaternion::operator==(const Quaternion &q) const {
    return (W == q[0] && X == q[1] && Y == q[2] && q[3] == Z);
}



