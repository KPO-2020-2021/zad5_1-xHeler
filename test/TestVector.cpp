#include "gtest/gtest.h"
#include "Vector.h"

TEST(Vector, emptyConstructor) {
    Vector v;
    Vector<3> w;
    Vector<3> result({0, 0, 0});
    EXPECT_EQ(v, w);
    EXPECT_EQ(v, result);
}

TEST(Vector, brackletOperator) {
    Vector<1> v;
    v[0] = 5;
    EXPECT_EQ(v[0], 5);
}

TEST(Vector, arrayConstructor) {
    Vector<5> v({1, 2, 3, 4, 5});
    EXPECT_EQ(v[1], 2);
}

TEST(Vector, additionOperator) {
    Vector<3> v({1, 1, 1});
    Vector<3> w({3, 2, 1});
    Vector<3> result({4, 3, 2});
    EXPECT_EQ(v + w, result);
}

TEST(Vector, additionOperatorExtra) {
    Vector<3> v({1, 1, 1});
    Vector<3> w({3, -9, 0});
    Vector<3> result({4, -8, 1});
    EXPECT_EQ(v += w, result);
}

TEST(Vector, substractionOperator) {
    Vector<3> v({9, 9, 9});
    Vector<3> w({1, 2, -3});
    Vector<3> result({8, 7, 12});
    EXPECT_EQ(v - w, result);
}

TEST(Vector, substractionOperatorExtra) {
    Vector<3> v({1, 1, 1});
    Vector<3> w({-3, 2, 0});
    Vector<3> result({4, -1, 1});
    EXPECT_EQ(v -= w, result);
}

TEST(Vector, multiplicationOperator) {
    Vector v({1, -1, 3});
    double constans = 5;
    Vector result({5, -5, 15});
    EXPECT_EQ(v * constans, result);
}

TEST(Vector, multiplicationOperatorEXTRA) {
    Vector v({0, 10, -10});
    double constans = 3;
    Vector result({0, 30, -30});
    EXPECT_EQ(v *= constans, result);
}

TEST(Vector, divisionOperator) {
    Vector v({0, 10, -10});
    double constans = 10;
    Vector result({0, 1, -1});
    EXPECT_EQ(v / constans, result);
}

TEST(Vector, divisionOperatorExtra) {
    Vector v({0, 10, -10});
    double constans = 10;
    Vector result({0, 1, -1});
    EXPECT_EQ(v /= constans, result);
}

TEST(Vector, scalarOperator) {
    Vector<2> v({2, 4});
    Vector<2> w({-1, -3});
    double result = -14;
    EXPECT_EQ(v % w, result);
}

TEST(Vector, moduloOfVector) {
    Vector<2> v({3, 4});
    double result = 5;
    EXPECT_EQ(v.getModulo(), result);
}

TEST(Vector, rotationEulerAngels) {
    Vector v_x({1, 0, 0});
    Vector v_y({0, 1, 0});
    Vector v_z({0, 0, 1});
    v_x.rotateByEulerAngles(0,90,0);
    v_y.rotateByEulerAngles(90,0,0);
    v_z.rotateByEulerAngles(0,90,0);

    EXPECT_EQ(v_x, Vector({0,0,-1}));
    EXPECT_EQ(v_y, Vector({0,0,1}));
    EXPECT_EQ(v_z, Vector({1,0,0}));
}





