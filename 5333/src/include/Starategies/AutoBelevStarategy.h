#pragma once

#include "curtinfrc/strategy/strategy.h"
#include "curtinfrc/PID.h"

#include "../Map.h"
#include "../Belev.h"

using namespace frc;
using namespace curtinfrc;

class AutoBelevStarategy : public Strategy {
public:
  enum component {
    Belevator,
    Intake,
    Claw
  };

  AutoBelevStarategy(BelevatorControl *_belev, component _part, double _power, int _t = 0) {
    belev = _belev;
    part = _part;
    power = _power;
    t = _t;
  };
  void start() override;
  void tick(double time) override;
  void stop() override;

private:
  BelevatorControl *belev;
  component part;
  double power;
  int t;
};
