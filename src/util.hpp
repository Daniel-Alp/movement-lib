#include "math.h"

inline double wrap_angle_radians(double theta) {
    while (theta  < -M_PI) {
        theta += 2 * M_PI;
    }
    while (theta > M_PI) {
        theta -= 2 * M_PI;
    }
    return theta;
}