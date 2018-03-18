#include "Starategies/BadAutoStarategy.h"

#include <iostream>

#include "curtinfrc/drivetrain.h"
#include "ControlMap.h"
#include "IO.h"
#include "Map.h"

using namespace std;

BadAutoStarategy::BadAutoStarategy(Drivetrain *_drive, double _power, int _t) {
  drive = _drive;
  power = _power;
  t = _t;
}

void BadAutoStarategy::start() {
  drive->set_left(0);
  drive->set_right(0);

  IO::get_instance()->left_motors[0]->SetSelectedSensorPosition(0, 0, 0);
  IO::get_instance()->right_motors[0]->SetSelectedSensorPosition(0, 0, 0);
}

void BadAutoStarategy::tick(double time) {
  if (time < t) { // FORWARD TIME
    double kp = 0.3;

    double err = IO::get_instance()->left_motors[0]->GetSelectedSensorPosition(0)/1440.0f - IO::get_instance()->right_motors[0]->GetSelectedSensorPosition(0)/1000.0f;
    err *= kp;
    cout << err << endl;
    drive->set_left((power - err));
    drive->set_right((power + err));
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
