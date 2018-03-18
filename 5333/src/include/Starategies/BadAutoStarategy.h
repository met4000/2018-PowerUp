#pragma once

#include "curtinfrc/strategy/strategy.h"
#include "curtinfrc/drivetrain.h"

using namespace curtinfrc;

class BadAutoStarategy : public Strategy {
public:
  BadAutoStarategy(Drivetrain *_drive, double _power, int _t);
  void start() override;
  void tick(double time) override;
  void stop() override;

private:
  Drivetrain *drive;
  double power;
  int t;
};
