#include "Drone.h"

Drone::Drone(double _scale, Vector<STANDARD_SIZE> position) {
    scale = _scale;
    trunk = Trunk(scale);
    setupBeams();
    setupRotors();
    translation(Vector({0, HEIGHT * scale / 2, 0}));

    orientationTemporary = 0;
    orientationTotal = Vector();
    translationTotal = Vector();
    liftVelocity = 0;
    rotorsVelocity = 0;
    flyVelocity = 0;
    rotationVelocity = 0;
    centerOfSymmetry = Vector();

    translation(position);
}

void Drone::draw() {
    trunk.draw();

    beams[0].draw();
    beams[1].draw();

    for (int i = 0; i < ROTORS; ++i) {
        rotors[i].draw();
    }
}

void Drone::translation(Vector<STANDARD_SIZE> translationVector) {
    centerOfSymmetry = centerOfSymmetry + translationVector;

    trunk.translation(translationVector);
    beams[0].translation(translationVector);
    beams[1].translation(translationVector);

    for (int i = 0; i < ROTORS; ++i) {
        rotors[i].translation(translationVector);
    }
}

void Drone::rotationMain(Vector<STANDARD_SIZE> rotations) {
    centerOfSymmetry.rotateByEulerAngles(rotations[0], rotations[1], rotations[2]);
    trunk.rotationMain(rotations);
    beams[0].rotationMain(rotations);
    beams[1].rotationMain(rotations);

    for (int i = 0; i < ROTORS; ++i) {
        rotors[i].rotationMain(rotations);
    }
}

void Drone::rotationLocal(Vector<STANDARD_SIZE> rotations) {
    Vector tmp = centerOfSymmetry * -1;
    translation(tmp);
    rotationMain(rotations);
    tmp = tmp * -1;
    translation(tmp);
    centerOfSymmetry = tmp;
}

void Drone::setColor(std::string _color) {
    color = _color;
    trunk.setColor(color);
    beams[0].setColor(color);
    beams[1].setColor(color);

    for (int i = 0; i < ROTORS; ++i) {
        rotors[i].setColor(color);
    }
}

void Drone::setupBeams() {
    double x = LENGHT * 1.4 * scale;
    double y = LENGHT * 0.12 * scale;
    double z = LENGHT * 0.08 * scale;
    double translationX = LENGHT * 0.4 * scale;

    beams[0] = Cuboid(x, y,z);
    beams[1] = Cuboid(x, y,z);

    beams[0].rotationMain(0, 90, 0);
    beams[0].translation(translationX, 0 ,0);

    beams[1].rotationMain(0, 90, 0);
    beams[1].translation(-translationX, 0 ,0);
}

void Drone::setupRotors() {
    for (int i = 0; i < ROTORS; ++i) {
        rotors[i] = Rotor(RADIUS * scale);
        rotors[i].rotationMain(Vector({0, 45, 0}));
    }
    double x = LENGHT * 0.40 * scale;
    double y = LENGHT * 0.12 * scale;
    double z = LENGHT * 0.68 * scale;

    rotors[0].translation(Vector({x, y, z}));
    rotors[1].translation(Vector({x, y, -z}));
    rotors[2].translation(Vector({-x, y, z}));
    rotors[3].translation(Vector({-x, y, -z}));
}

void Drone::rotorsActivate(double velocity) {
    rotors[0].rotationLocal(Vector({0, velocity, 0}));
    rotors[1].rotationLocal(Vector({0, -velocity, 0}));
    rotors[2].rotationLocal(Vector({0, -velocity, 0}));
    rotors[3].rotationLocal(Vector({0, velocity, 0}));
}


void Drone::liftOf(double alititude) {
    if (rotorsVelocity < ROTORS_V_MAX) rotorsVelocity += LIFT_DELTA * 2;
    if (rotorsVelocity > ROTORS_V_MIN) liftVelocity += LIFT_DELTA * 0.75;
    if (centerOfSymmetry[1] > alititude) {
        liftVelocity = 0;
    }
    rotorsActivate(rotorsVelocity);
    translation(Vector({0, liftVelocity, 0}));
}

void Drone::landing() {
    if (rotorsVelocity > ROTORS_V_MIN) rotorsVelocity -= LIFT_DELTA * 2;
    if (rotorsVelocity < ROTORS_V_MAX * 0.8) liftVelocity += LIFT_DELTA * 0.75;
    if (centerOfSymmetry[1] <= 0) {
        liftVelocity = 0;
        rotorsVelocity = 0;
        translation(Vector({0, HEIGHT * scale / 2 + centerOfSymmetry[1] * -1, 0}));
    }
    rotorsActivate(rotorsVelocity);
    translation(Vector({0, -liftVelocity, 0}));
}

void Drone::rotation(double angle) {
    if (rotationVelocity == 0 && angle > 0) rotationVelocity = 1;
    else if (rotationVelocity== 0 && angle < 0) rotationVelocity = -1;

    if (angle >= 0 && orientationTemporary >= angle) {
        rotationVelocity = 0;
    } else if (angle <= 0 && orientationTemporary < angle) {
        rotationVelocity = 0;
    }

    orientationTemporary += rotationVelocity;
    rotorsActivate(rotorsVelocity);
    rotationLocal(Vector({0, rotationVelocity, 0}));
}

void Drone::forward() {
    if (flyVelocity < 5) flyVelocity += LIFT_DELTA * 0.25;
    Vector distance = calculateDistance(flyVelocity, orientationTotal);
    rotorsActivate(rotorsVelocity);
    translation(distance);
    translationTotal = translationTotal + distance;
}


double Drone::getOrientationTemporary() const {
    return orientationTemporary;
}

const Vector<STANDARD_SIZE> &Drone::getOrientationTotal() const {
    return orientationTotal;
}

const Vector<STANDARD_SIZE> &Drone::getTranslationTotal() const {
    return translationTotal;
}

double Drone::getScale() const {
    return scale;
}

double Drone::getLiftVelocity() const {
    return liftVelocity;
}

double Drone::getRotorsVelocity() const {
    return rotorsVelocity;
}

double Drone::getFlyVelocity() const {
    return flyVelocity;
}

double Drone::getRotationVelocity() const {
    return rotationVelocity;
}

void Drone::setOrientationTemporary(double orientationTemporary) {
    Drone::orientationTemporary = orientationTemporary;
}

void Drone::setOrientationTotal(const Vector<STANDARD_SIZE> &orientationTotal) {
    Drone::orientationTotal = orientationTotal;
}

Vector<STANDARD_SIZE> calculateDistance(double distance, Vector<STANDARD_SIZE> orientation) {
    Vector unit = Vector({distance, 0, 0});
    unit.rotateByEulerAngles(orientation[0], orientation[1], orientation[2]);
    return unit;
}

Vector<STANDARD_SIZE> Drone::getCenterOfSymmetry() {
    return centerOfSymmetry;
}


