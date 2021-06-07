#pragma once

#include "Trunk.h"
#include "Rotor.h"

const int ROTORS = 4;
const int BEAMS = 2;
const double ROTORS_V_MIN = 12;
const double ROTORS_V_MAX = 15;
const double LIFT_DELTA = 0.1;


class Drone : public Object {
private:
    Trunk trunk;
    std::array<Cuboid, BEAMS> beams;
    std::array<Rotor, ROTORS> rotors;
    double orientationTemporary;
    Vector<STANDARD_SIZE> orientationTotal;
    Vector<STANDARD_SIZE> translationTotal;
    double scale;
    double liftVelocity;
    double rotorsVelocity;
    double flyVelocity;
    double rotationVelocity;


    void setupBeams();

    void setupRotors();

    void translation(Vector<STANDARD_SIZE> translationVector) override;

    void rotationMain(Vector<STANDARD_SIZE> rotations) override;

    void rotationLocal(Vector<STANDARD_SIZE> rotations) override;

public:
    Drone(double _scale = 1, Vector<STANDARD_SIZE> position = Vector());

    void draw() override;

    void setColor(std::string _color) override;

    std::string getColor() {return color;}

    void rotorsActivate(double velocity);

    void liftOf(double alititude);

    void landing();

    void rotation(double angle);

    void forward();

    double getOrientationTemporary() const;

    const Vector<STANDARD_SIZE> &getOrientationTotal() const;

    const Vector<STANDARD_SIZE> &getTranslationTotal() const;

    double getScale() const;

    double getLiftVelocity() const;

    double getRotorsVelocity() const;

    double getFlyVelocity() const;

    double getRotationVelocity() const;

    Vector<STANDARD_SIZE> getCenterOfSymmetry() override;

    void setOrientationTemporary(double orientationTemporary);

    void setOrientationTotal(const Vector<STANDARD_SIZE> &orientationTotal);

};

Vector<STANDARD_SIZE> calculateDistance(double distance, Vector<STANDARD_SIZE> orientation);