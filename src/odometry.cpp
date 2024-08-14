#include <cmath>
#include "util.hpp"
#include "translation.hpp"
#include "chassis.hpp"
#include "odometry.hpp"
#include "logging.hpp"

Pose global_pose{};

void update_global_pose(double ds, double dtheta) {
    double local_dx = 0;
    double local_dy = 0;

    if (std::abs(dtheta) < 1E-9) {
        // Moving in a straight line (avoid division by zero)
        local_dx = 0;
        local_dy = ds;
    } else {
        // Moving in a circular arc
        local_dx = (ds/dtheta) * (1-std::cos(dtheta));
        local_dy = (ds/dtheta) * std::sin(dtheta);
    }

    Vector local_displacement{local_dx, local_dy};

    // Convert local displacement to global displacement
    Vector global_displacement = local_displacement.rotate_by(global_pose.theta);

    global_pose.coordinates += global_displacement;
    global_pose.theta = wrap_angle_radians(global_pose.theta + dtheta);
}

void localization_loop() {
    double s_l = 0;
    double s_l_prev = 0;
    double s_r = 0;
    double s_r_prev = 0;

    double theta = 0;
    double theta_prev = 0;

    while (true) {
        s_l = get_left_wheel_position();
        s_r = get_right_wheel_position();
        theta = get_heading_radians();

        double ds_l = s_l - s_l_prev;
        double ds_r = s_r - s_r_prev;

        double ds = (ds_l+ds_r) / 2;
        double dtheta = wrap_angle_radians(theta - theta_prev);

        update_global_pose(ds, dtheta);

        s_l_prev = s_l;
        s_r_prev = s_r;
        theta_prev = theta;

        pros::delay(10);
    }
}