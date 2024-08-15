#include "math.h"

inline double sgn(double x) {
    if (x < 0) {
        return -1;
    }
    if (x > 0) {
        return 1;
    }
    return 0;
}

inline double wrap_angle_radians(double theta) {
    while (theta  < -M_PI) {
        theta += 2 * M_PI;
    }
    while (theta > M_PI) {
        theta -= 2 * M_PI;
    }
    return theta;
}

inline double radians_to_degrees(double theta) {
    return theta * (180/M_PI);
}

inline double degrees_to_radians(double theta) {
    return theta * (M_PI/180);
}