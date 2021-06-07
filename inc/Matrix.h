#pragma once

#include <iostream>
#include <iomanip>
#include <array>

const int STREAM_PRECISION = 5;
const int STANDARD_SIZE = 3;

template<int SIZE = STANDARD_SIZE>
class Matrix {
private:
    std::array<double, SIZE * SIZE> numbers;
public:
    Matrix() { numbers.fill(0); }

    explicit Matrix(int diagonal);

    explicit Matrix(std::array<double, SIZE * SIZE> args) : numbers(args) {};

    Matrix operator+(const Matrix &v);

    Matrix operator-(const Matrix &v);

    Matrix operator*(const Matrix &v);

    template<class D = double>
    Matrix operator*(const D &v);

    const double &operator[](int i) const;

    double &operator[](int index);
};

template<int SIZE>
Matrix<SIZE> Matrix<SIZE>::operator+(const Matrix &v) {
    Matrix<SIZE> result;
    for (int i = 0; i < SIZE; i++) {
        result[i] = numbers[i] + v[i];
    }
    return result;
}

template<int SIZE>
Matrix<SIZE> Matrix<SIZE>::operator-(const Matrix &v) {
    Matrix<SIZE> result;
    for (int i = 0; i < SIZE; i++) {
        result[i] = numbers[i] - v[i];
    }
    return result;
}

template<int SIZE>
Matrix<SIZE> Matrix<SIZE>::operator*(const Matrix &v) {
    Matrix<SIZE> result;
    for (int i = 0; i < SIZE; i++) {
        for (int j = 0; j < SIZE; j++) {
            for (int k = 0; k < SIZE; k++) {
                result[j + (SIZE * i)]  += numbers[k + (SIZE * i)] * v[j + (SIZE * k)];
            }
        }
    }
    return result;
}

template<int SIZE>
template<class D>
Matrix<SIZE> Matrix<SIZE>::operator*(const D &v) {
    Matrix<SIZE> result;
    for (int i = 0; i < SIZE; i++) {
        result[i] = numbers[i] * v;
    }
    return result;
}

template<int SIZE>
const double &Matrix<SIZE>::operator[](int index) const {
    if (index >= SIZE * SIZE || index < 0) throw std::invalid_argument("Index out of range!");
    return numbers[index];
}

template<int SIZE>
double &Matrix<SIZE>::operator[](int index) {
    if (index >= SIZE * SIZE || index < 0) throw std::invalid_argument("Index out of range!");
    return numbers[index];
}

template<int SIZE>
Matrix<SIZE>::Matrix(int diagonal) {
    numbers.fill(0);
    for (int i = 0; i < SIZE; i++) {
        numbers[i + (SIZE * i)] = diagonal;
    }
}

template<int SIZE>
bool operator==(const Matrix<SIZE> &v, const Matrix<SIZE> &w) {
    for (int i = 0; i < SIZE; i++) {
        if (v[i] != w[i]) return false;
    }
    return true;
}


template<int SIZE>
std::ostream &operator<<(std::ostream &ost, const Matrix<SIZE> &m) {
    ost << std::setprecision(STREAM_PRECISION) << std::fixed;
    for (int i = 0; i < SIZE; i++) {
        ost << "[ ";
        for (int j = 0; j < SIZE; j++) {
            ost << m[j + (SIZE * i)] << " ";
        }
        ost << "]" << std::endl;
    }
    return ost;

}

