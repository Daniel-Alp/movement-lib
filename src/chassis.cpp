#include <vector>
#include <numeric>
#include "main.h"
#include "chassis.hpp"

pros::Controller master(pros::E_CONTROLLER_MASTER);
pros::MotorGroup left_motors({18, -19, -20});
pros::MotorGroup right_motors({-11, 12, 14}); 
pros::IMU imu(15);

void set_left_voltage(double voltage) {
    left_motors.move_voltage(voltage);
}

void set_right_voltage(double voltage) {
    right_motors.move_voltage(voltage);
}

// inches/s
double get_left_wheel_velocity() {
    std::vector<double> encoder_pos = left_motors.get_actual_velocity_all();
    double avg = std::accumulate(encoder_pos.begin(), encoder_pos.end(), 0.0) / encoder_pos.size();

    return WHEEL_DIAMETER * M_PI * WHEEL_TO_ENCODER_RATIO * avg / 60;
}

// inches/s
double get_right_wheel_velocity() {
    std::vector<double> encoder_pos = right_motors.get_actual_velocity_all();
    double avg = std::accumulate(encoder_pos.begin(), encoder_pos.end(), 0.0) / encoder_pos.size();

    return WHEEL_DIAMETER * M_PI * WHEEL_TO_ENCODER_RATIO * avg / 60;
}

// inches
double get_left_wheel_position() {
    std::vector<double> encoder_pos = left_motors.get_position_all();
    double avg = std::accumulate(encoder_pos.begin(), encoder_pos.end(), 0.0) / encoder_pos.size();

    return WHEEL_DIAMETER * M_PI * WHEEL_TO_ENCODER_RATIO * avg;
}

// inches
double get_right_wheel_position() {
    std::vector<double> encoder_pos = right_motors.get_position_all();
    double avg = std::accumulate(encoder_pos.begin(), encoder_pos.end(), 0.0) / encoder_pos.size();
    
    return WHEEL_DIAMETER * M_PI * WHEEL_TO_ENCODER_RATIO * avg;
}

void tare_left_encoder_position() {
    left_motors.tare_position_all();
}

void tare_right_encoder_position() {
    right_motors.tare_position_all();
}

double get_heading_radians() {
    return imu.get_heading() * (M_PI/180);
}