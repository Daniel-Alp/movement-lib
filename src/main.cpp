#include "main.h"
#include "chassis.hpp"
#include "odometry.hpp"
#include "logging.hpp"

void initialize() {
    left_motors.set_gearing_all(pros::E_MOTOR_GEAR_600);
    right_motors.set_gearing_all(pros::E_MOTOR_GEAR_600);

    left_motors.set_encoder_units_all(pros::E_MOTOR_ENCODER_ROTATIONS);
    right_motors.set_encoder_units_all(pros::E_MOTOR_ENCODER_ROTATIONS);

    imu.reset();
    while(imu.is_calibrating()) {
        pros::delay(10);
    }
}

void disabled() {}

void competition_initialize() {}

void autonomous() {}

void opcontrol() {
	localization_loop();
}