#pragma once

#include <cmath>
#include <iomanip>
#include <iostream>
#include <array>
#include "Quaternion.h"

const double PRECISION_RIFFLE = 0.001;

template<int SIZE = STANDARD_SIZE>
class Vector {
private:
    std::array<double, SIZE> numbers;
public:
    Vector<SIZE>() { numbers.fill(0); };

    Vector(std::array<double, SIZE> args) : numbers(args) {};

    Vector<SIZE> operator+(const Vector<SIZE> &v);

    Vector<SIZE> operator+=(const Vector<SIZE> &v);

    Vector<SIZE> operator-(const Vector<SIZE> &v);

    Vector<SIZE> operator-=(const Vector<SIZE> &v);

    Vector<SIZE> operator*(const Vector<SIZE> &v);

    Vector<SIZE> operator*=(const Vector<SIZE> &v);

    double operator%(const Vector<SIZE> &v);

    const double &operator[](int index) const;

    double &operator[](int index);

    double getModulo();

    void rotateByEulerAngles(double angle_x, double angle_y, double angle_z);

    void translation(Vector<SIZE> translationVector);
};

template<int SIZE>
Vector<SIZE> Vector<SIZE>::operator+(const Vector<SIZE> &v) {
    Vector<SIZE> result;
    for (int i = 0; i < SIZE; i++) {
        result[i] = numbers[i] + v[i];
    }
    return result;
}

template<int SIZE>
Vector<SIZE> Vector<SIZE>::operator+=(const Vector<SIZE> &v) {
    Vector<SIZE> result;
    for (int i = 0; i < SIZE; i++) {
        result[i] = numbers[i] + v[i];
    }
    return result;
}

template<int SIZE>
Vector<SIZE> Vector<SIZE>::operator-(const Vector<SIZE> &v) {
    Vector<SIZE> result;
    for (int i = 0; i < SIZE; i++) {
        result[i] = numbers[i] - v[i];
    }
    return result;
}

template<int SIZE>
Vector<SIZE> Vector<SIZE>::operator-=(const Vector<SIZE> &v) { // a = a - b >> a -= b;
    Vector<SIZE> result;
    for (int i = 0; i < SIZE; i++) {
        result[i] = numbers[i] - v[i];
    }
    return result;
}

template<int SIZE>
Vector<SIZE> Vector<SIZE>::operator*(const Vector<SIZE> &v) {
    Vector<SIZE> result;
    for (int i = 0; i < SIZE; i++) {
        result[i] = numbers[i] * v[i];
    }
    return result;
}

template<int SIZE>
Vector<SIZE> Vector<SIZE>::operator*=(const Vector<SIZE> &v) {
    Vector<SIZE> result;
    for (int i = 0; i < SIZE; i++) {
        result[i] = numbers[i];
        result[i] *= v[i];
    }
    return result;
}

template<int SIZE>
double Vector<SIZE>::operator%(const Vector<SIZE> &v) {
    double result;
    for (int i = 0; i < SIZE; i++) {
        result += numbers[i] * v[i];
    }
    return result;
}

template<int SIZE>
const double &Vector<SIZE>::operator[](int index) const {
    if (index >= SIZE || index < 0) throw std::invalid_argument("Index out of range!");
    return numbers[index];
}

template<int SIZE>
double &Vector<SIZE>::operator[](int index) {
    if (index >= SIZE || index < 0) throw std::invalid_argument("Index out of range!");
    return numbers[index];
}

template<int SIZE>
double Vector<SIZE>::getModulo() {
    double tmp;
    for (int i = 0; i < SIZE; i++) {
        tmp += numbers[i] * numbers[i];
    }
    return sqrt(tmp);
}

template<int SIZE>
bool operator==(const Vector<SIZE> &v, const Vector<SIZE> &w) {
    for (int i = 0; i < SIZE; i++) {
        if (std::abs(v[i] - w[i]) >= PRECISION_RIFFLE) return false;
    }
    return true;
}

template<int SIZE>
Vector<SIZE> operator*(const Vector<SIZE> &v, const int &w) {
    Vector<SIZE> result;
    for (int i = 0; i < SIZE; i++) {
        result[i] = w * v[i];
    }
    return result;
}

template<int SIZE>
Vector<SIZE> operator*=(const Vector<SIZE> &v, const int &w) {
    Vector<SIZE> result;
    for (int i = 0; i < SIZE; i++) {
        result[i] = v[i];
        result[i] *= w;
    }
    return result;
}

template<int SIZE>
Vector<SIZE> operator/(const Vector<SIZE> &v, const double &w) {
    Vector<SIZE> result;
    for (int i = 0; i < SIZE; i++) {
        result[i] = v[i] / w;
    }
    return result;
}

template<int SIZE>
Vector<SIZE> operator/=(const Vector<SIZE> &v, const int &w) {
    Vector<SIZE> result;
    for (int i = 0; i < SIZE; i++) {
        result[i] = v[i];
        result[i] /= w;
    }
    return result;
}

template<int SIZE>
double distanceBetweenTwoVectors(const Vector<SIZE> &v, const Vector<SIZE> &w) {
    double tmp;
    for (int i = 0; i < SIZE; i++) {
        tmp += pow(abs(v[i] - w[i]), 2);
    }
    return sqrt(tmp);
}

template<int SIZE>
void Vector<SIZE>::translation(Vector<SIZE> translationVector) {
    for (int i = 0; i < SIZE; i++) {
        numbers[i] += translationVector[i];
    }
}


template<int SIZE>
std::ostream &operator<<(std::ostream &ost, const Vector<SIZE> &Vec) {
    ost << std::setprecision(STREAM_PRECISION) << std::fixed;

    for (int i = 0; i < SIZE - 1; i++) {
        ost << Vec[i] << ",";
    }
    ost << Vec[SIZE - 1];
    return ost;

}

template<int SIZE>
std::istream &operator>>(std::istream &ist, Vector<SIZE> &Vec) {
    double tmp = 0;
    for (int i = 0; i < SIZE; i++) {
        std::cout << i + 1 << ". number: ";
        ist >> tmp;
        if (ist.good()) Vec[i] = tmp;
        else Vec[i] = 2137;
    }
    return ist;
}

template<int SIZE>
Vector<SIZE> operator*(const Matrix<SIZE> &m, const Vector<SIZE> &v) {
    Matrix<SIZE> tmp;
    Vector<SIZE> result;
    for (int i = 0; i < SIZE; i++) {
        tmp[0][i] = v[i];
    }
    tmp = m * tmp;
    for (int j = 0; j < SIZE; j++) {
        result[j] = tmp[0][j];
    }

    return result;
}

template<int SIZE>
void Vector<SIZE>::rotateByEulerAngles(double angle_x, double angle_y, double angle_z) { // ZYX
    Quaternion position(0, numbers[0], numbers[1], numbers[2]);
    angle_x = (M_PI / 180) * angle_x;
    angle_y = (M_PI / 180) * angle_y;
    angle_z = (M_PI / 180) * angle_z;

    // x-axis
    Quaternion q_x(std::cos(angle_x / 2), std::sin(angle_x / 2), 0, 0);

    // y-axis
    Quaternion q_y(std::cos(angle_y / 2), 0, std::sin(angle_y / 2), 0);

    // z-axis
    Quaternion q_z(std::cos(angle_z / 2), 0, 0, std::sin(angle_z / 2));

    position = q_x * position * q_x.getConjugate();
    position = q_y * position * q_y.getConjugate();
    position = q_z * position * q_z.getConjugate();

    numbers[0] = position[1];
    numbers[1] = position[2];
    numbers[2] = position[3];
}
