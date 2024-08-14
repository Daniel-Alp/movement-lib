#include "main.h"
#include "util.hpp"
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

double map_input_to_voltage(double input) {
    // This mapping ignores smaller input values to avoid jerky movement.
    return sgn(input) * (input/127) * (input/127) * 12000; // Input ranges -127 to 127, voltage ranges -12000 to 12000
}

void opcontrol() {
    pros::Task localization([] {
        localization_loop();
    });

    pros::Task logging([=] {
        while(true) {
            // Round values so that messages take up less bytes and can be sent at a greater rate
            Pose rounded_global_pose{
                std::round(global_pose.coordinates.x * 1000) / 1000,
                std::round(global_pose.coordinates.y * 1000) / 1000,
                std::round(global_pose.theta * 1000) / 1000,
            };

            Message msg{"odometry", rounded_global_pose};
            std::cout << static_cast<json>(msg) << std::endl;
            pros::delay(20);
        }
    });

    while(true) {
        int throttle = master.get_analog(pros::E_CONTROLLER_ANALOG_LEFT_Y);
        int turn = master.get_analog(pros::E_CONTROLLER_ANALOG_RIGHT_X);

        double left_voltage = map_input_to_voltage(throttle+turn); // Constant used to map joystick input to voltage
        double right_voltage = map_input_to_voltage(throttle-turn);

        set_left_velocity(left_voltage);
        set_right_velocity(right_voltage);

        pros::delay(10);
    }
}