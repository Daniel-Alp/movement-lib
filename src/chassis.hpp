#pragma once
#include "main.h"

const double WHEEL_DIAMETER = 3.25;
const double WHEEL_TO_ENCODER_RATIO = 36.0/60.0;

extern pros::MotorGroup left_motors;
extern pros::MotorGroup right_motors;

extern pros::IMU imu;

void set_left_velocity(double voltage);

void set_right_velocity(double voltage);

double get_left_wheel_position();

double get_right_wheel_position();

void tare_left_encoder_position();

void tare_right_encoder_position();

double get_heading_radians();