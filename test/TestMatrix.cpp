#include "gtest/gtest.h"
#include "Matrix.h"

TEST(Matrix, emptyConstructor) {
    Matrix<1> a;
    Matrix<1> b({0});
    EXPECT_EQ(a, b);
}

TEST(Matrix, brackletOperator) {
    Matrix<1> a;
    a[0] = 9;
    EXPECT_EQ(a[0], 9);
}

TEST(Matrix, arrayConstructor) {
    Matrix<2> a({1, 2, 3, 4});
    EXPECT_EQ(a[1], 2);
}

TEST(Matrix, additionOperator) {
    Matrix<2> a({1, 2, 3, 4});
    Matrix<2> b({-1, -2, -3, -4});
    EXPECT_EQ(a + b, Matrix<2>(0));
}

TEST(Matrix, substractionOperator) {
    Matrix<2> a({1, 2, 3, 4});
    Matrix<2> b({-1, -2, -3, -4});
    Matrix<2> result({2, 4, 6, 8});
    EXPECT_EQ(a - b, result);
}

TEST(Matrix, multiplicationOperator) {
    Matrix<2> a({1, 2, 3, 4});
    Matrix<2> b({1, 2, 3, 4});
    Matrix<2> result({7, 10, 15, 22});
    EXPECT_EQ(a * b, result);
}

TEST(Matrix, constansMultiplicationOperator) {
    Matrix<2> a({1, 2, 3, 4});
    double constans = 5;
    Matrix<2> result({5, 10, 15, 20});
    EXPECT_EQ(a * constans, result);
}
