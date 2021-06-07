#pragma once

/**
 *  [S] - LiftOf | value = altitude
 *  [F] - forward fly | value = distance
 *  [L] - landing | value = insignificant
 *  [R] - rotation | value = angle
 */

struct Command {
    char directing;
    double value;
};
