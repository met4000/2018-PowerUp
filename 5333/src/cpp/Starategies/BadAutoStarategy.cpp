#include "Starategies/BadAutoStarategy.h"

#include <iostream>

#include "curtinfrc/drivetrain.h"
#include "ControlMap.h"

#include "Map.h"

using namespace std;

BadAutoStarategy::BadAutoStarategy(Drivetrain *_drive, double _throttle) {
  drive = _drive;
  throttle = _throttle;
}

void BadAutoStarategy::start() {
  drive->set_left(0);
  drive->set_right(0);
  SmartDashboard::PutNumber("Throttle:", throttle);
}

void BadAutoStarategy::tick(double time) {
  if (time < 3500) { // FORWARD TIME
    drive->set_left(throttle);
    drive->set_right(throttle);
  } else {
    this->done = true;
    drive->set_left(0);
    drive->set_right(0);
  }
}

void BadAutoStarategy::stop() {
  drive->set_left(0);
  drive->set_right(0);
}
