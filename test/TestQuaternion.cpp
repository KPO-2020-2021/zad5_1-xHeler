#include "gtest/gtest.h"
#include "Quaternion.h"

TEST(Quaternion, brackletOperator) {
    Quaternion q;
    q[0] = 5;
    EXPECT_EQ(q[0], 5);
}

TEST(Quaternion, emptyConstructor) {
    Quaternion q;
    EXPECT_EQ(q[0], 1);
    EXPECT_EQ(q[1], 0);
    EXPECT_EQ(q[2], 0);
    EXPECT_EQ(q[3], 0);
}

TEST(Quaternion, simpleConstructor) {
    Quaternion q(1, 2, 3, 4);
    EXPECT_EQ(q[0], 1);
    EXPECT_EQ(q[1], 2);
    EXPECT_EQ(q[2], 3);
    EXPECT_EQ(q[3], 4);
}

TEST(Quaternion, getRotationMatrix) {
    Quaternion q;
    Matrix rotation = q.getRotationMatrix();
    Matrix result(1);
    EXPECT_EQ(rotation, result);
}

TEST(Quaternion, addiotionOperation) {
    Quaternion q(1, 2, 3, 4);
    Quaternion w(-1, -2, -3, -4);
    Quaternion result(0, 0, 0, 0);
    EXPECT_EQ(q + w, result);
}

TEST(Quaternion, multiplicationOperation) {
    Quaternion q(1, 2, 3, 4);
    Quaternion w(1, 2, 3, 4);
    Quaternion result(-28, 4, 6, 8);
    EXPECT_EQ(q * w, result);
}

TEST(Quaternion, conjugate) {
    Quaternion q(1, 2, 3, 4);
    Quaternion result(1, -2, -3, -4);
    EXPECT_EQ(q.getConjugate(), result);
}

