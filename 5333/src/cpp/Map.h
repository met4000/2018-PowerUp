#pragma once

#include "WPILib.h"

#define DRIVER_TRAINING 1

namespace Map { // Map ports
  struct Controllers {
    #ifdef XBOX_CONTROL
    static const int xbox = 0;
    static constexpr double deadzone = 0.04;

    #elif JOY_CONTROL
    static constexpr int joy[2] = {0, 1};
    static constexpr double deadzone = 0.08;

    #elif DRIVER_TRAINING
    static constexpr int joy[2] = {0, 1};
    static const int xbox = 2;
    static constexpr double deadzone = 0.08;

    #endif
  };

  struct Sensors { };

  struct Motors {
    static constexpr int left_motors[2] = {32, 34};
    static constexpr int right_motors[2] = {36, 35};

    static constexpr int belev_motors[1] = {37};

    static constexpr int intake_motors[2][1] = {{38}, {39}};
  };

  struct Pneumatics {
    static constexpr int intake_solenoids[2][2] = {{1, 2}, {2, 4}};
    static constexpr int claw_solenoids[1][2] = {{0, 0}};
  };

  struct Robot { // Robot stats
    static constexpr float max_v = 9.8;
    static constexpr float max_a = 3;
    static constexpr float max_j = 60;
    static constexpr float wheel_diameter = 6; // Inches
    static constexpr float track_width = 0.61; // Metres
    static const int encoder_ticks_per_rot = 1000;
  };
}
