#include <vector>
#include "main.h"
#include "util.hpp"
#include "chassis.hpp"
#include "autonomous.hpp"
#include "logging.hpp"

Segment::Segment(double x, double v, double a) : x(x), v(v), a(a) {}

void move_straight(double x_goal) {
    // Generate trajectory (assume start and end velocity are 0 because it simplifies the calculations)
    bool reverse = false;
    if (x_goal < 0) {
        reverse = true;
        x_goal *= -1;
    }

    // All of the following values are magnitudes (positive).
    double v_max = std::min(MAX_VELOCITY, std::sqrt(x_goal * MAX_ACCELERATION));

    double t_speedup = v_max / MAX_ACCELERATION;
    double x_speedup = v_max * 0.5 * t_speedup;

    double t_slowdown = t_speedup;
    double x_slowdown = x_speedup;

    double x_cruise = x_goal - x_speedup - x_slowdown;
    double t_cruise = x_cruise / v_max;

    double t_total = t_speedup + t_cruise + t_slowdown;

     std::vector<Segment> trajectory{};
    trajectory.reserve(t_total / 0.01);

    double t = 0;
    double x = 0;
    double v = 0;
    double v_prev = 0;
    double a = 0;

    while (t <= t_total) {
        if (t <= t_speedup) {
            v = MAX_ACCELERATION * t;
        } else if (t <= t_speedup + t_cruise) {
            v = v_max;
        } else {
            v = v_max - MAX_ACCELERATION * (t - t_speedup - t_cruise);
        }
        a = (v - v_prev) / 0.01;
        x += (v + v_prev) * 0.5 * 0.01; // Trapezoidal integration.

        trajectory.emplace_back(x, v, a);

        v_prev = v;
        t += 0.01;
    }
    trajectory.emplace_back(x_goal, 0, 0);

    // Reverse if x_goal was negative
    if (reverse) {
        for (Segment& segment : trajectory) {
            segment.x *= -1;
            segment.v *= -1;
            segment.a *= -1;
        }
    }

    // Follow the generated trajectory
    const double ALLOWED_ERROR = 2.5; // inches

    double right_error = 0;
    double left_error = 0;
    double right_error_prev = 0;
    double left_error_prev = 0;
    
    int index = 0;

    auto calculate_voltage = [](double error, double error_prev, double v, double a) -> double {
        const double kV = 1/MAX_VELOCITY;
        const double kA = 0.35/MAX_ACCELERATION;
        const double kP = 0.04; 
        const double kD = 0.012;

        double feedforward = kV*v + kA*a;
        double feedback = kP*error + kD * ((error-error_prev) / 0.01);

        return (feedforward + feedback) * 12000; 
    };

    double right_x_init = get_right_wheel_position();
    double left_x_init = get_left_wheel_position();

    do {
        Segment segment = trajectory[index];

        right_error = segment.x - (get_right_wheel_position() - right_x_init);
        left_error = segment.x - (get_left_wheel_position() - left_x_init);

        double right_voltage = calculate_voltage(right_error, right_error_prev, segment.v, segment.a);
        double left_voltage = calculate_voltage(left_error, left_error_prev, segment.v, segment.a);

        set_left_voltage(left_voltage);
        set_right_voltage(right_voltage);
        
        right_error_prev = right_error;
        left_error_prev = left_error;

        if (index % 3 == 0) {
            Velocities vels{get_left_wheel_velocity(), get_right_wheel_velocity(), segment.v};
            Message msg{"velocity", vels};
            std::cout << static_cast<json>(msg) << std::flush;
        }

        if (index < trajectory.size() - 1) {
            index++;
        }

        pros::delay(10);
    } while (index < trajectory.size() - 1 ||
            std::abs(left_error) > ALLOWED_ERROR || 
            std::abs(right_error) > ALLOWED_ERROR); 
            
    set_left_voltage(0);
    set_right_voltage(0);
}

void turn_to(double theta_goal) {
    //TODO   
}