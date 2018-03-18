#pragma once

#include "curtinfrc/strategy/strategy.h"
#include "curtinfrc/drivetrain.h"

using namespace frc;
using namespace curtinfrc;

class AutoDriveStarategy : public Strategy {
public:
  AutoDriveStarategy(Drivetrain *_drive, double _powerL, double _powerR, int _t) {
    drive = _drive;
    powerL = _powerL;
    powerR = _powerR;
    t = _t;
  };

  void start() override {
    drive->set_left(powerL);
    drive->set_right(powerR);
  };

  void tick(double time) override {
    if (time > t) this->done = true;
  };

  void stop() override {
    drive->set_left(0);
    drive->set_right(0);
  };

private:
  Drivetrain *drive;
  double powerL, powerR;
  int t;
};
