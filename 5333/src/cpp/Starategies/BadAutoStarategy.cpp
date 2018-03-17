#include "Starategies/BadAutoStarategy.h"

#include <iostream>

#include "curtinfrc/drivetrain.h"
#include "ControlMap.h"
#include "IO.h"
#include "Map.h"

using namespace std;

BadAutoStarategy::BadAutoStarategy(Drivetrain *_drive, double _throttle) {
  drive = _drive;
  throttle = _throttle;
}

void BadAutoStarategy::start() {
  drive->set_left(0);
  drive->set_right(0);

  IO::get_instance()->left_motors[0]->SetSelectedSensorPosition(0, 0, 0);
  IO::get_instance()->right_motors[0]->SetSelectedSensorPosition(0, 0, 0);


  SmartDashboard::PutNumber("Throttle:", throttle);
}

void BadAutoStarategy::tick(double time) {
  if (time < 3000) { // FORWARD TIME
    double kp = 0.3;

    double err = -IO::get_instance()->left_motors[0]->GetSelectedSensorPosition(0)/1440.0f + IO::get_instance()->right_motors[0]->GetSelectedSensorPosition(0)/1000.0f;
    err *= kp;
    cout << err << endl;
    drive->set_left(-(0.6 - err));
    drive->set_right(-(0.6 + err));
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
