#pragma once
#include "main.h"

const double WHEEL_DIAMETER = 3.25; // inches
const double WHEEL_TO_ENCODER_RATIO = 36.0/48.0;

const double MAX_VELOCITY = 85; // inches/s
const double MAX_ACCELERATION = 145; // inches/s^2 

extern pros::Controller master;

extern pros::MotorGroup left_motors;
extern pros::MotorGroup right_motors;

extern pros::IMU imu;

void set_left_voltage(double voltage);

void set_right_voltage(double voltage);

double get_left_wheel_velocity();

double get_right_wheel_velocity();

double get_left_wheel_position();

double get_right_wheel_position();

void tare_left_encoder_position();

void tare_right_encoder_position();

double get_heading_radians();