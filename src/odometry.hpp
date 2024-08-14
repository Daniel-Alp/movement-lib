#pragma once
#include "translation.hpp"

extern Pose global_pose;

// Update global pose assuming robot travels in a circular arc
void update_global_pose(double ds, double dtheta);

// PROS task for localizing the robot on the game field
void localization_loop();