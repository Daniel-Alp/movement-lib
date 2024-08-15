#pragma once

// Segment of a trajectory
struct Segment {
    double x;
    double v;
    double a;

    Segment(double x, double v, double a);
};

void move_straight(double x_goal);

void turn_to(double theta_goal);