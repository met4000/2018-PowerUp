#pragma once

#include "curtinfrc/strategy/strategy.h"

class BelevatorControl {
public:
  BelevatorControl() {};

  enum class Gear {
    High,
    Low
  };

  void tick();
  void lift(double power);
  void winch_brake(bool enabled);
  void claw(bool open);
  void intake(double left, double right);
  void intake(double power);

  curtinfrc::StrategyController &strategy_controller() {
    return BelevatorControl::strat_controller;
  }

  int belev_position;

private:
  curtinfrc::StrategyController strat_controller;
};
