#pragma once

#include "curtinfrc/strategy/strategy.h"
#include "curtinfrc/component/Component.h"

using namespace curtinfrc;

class BelevatorControl : public Component {
public:
  BelevatorControl() {};

  enum class Gear {
    High,
    Low
  };

  void tick() override;
  void lift(double power);
  void winch_brake(bool enabled);
  void claw(bool open);
  void intake(double left, double right);
  void intake(double power);

  int belev_position;
};
