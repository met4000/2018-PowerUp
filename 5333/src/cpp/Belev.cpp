#include "Belev.h"
#include "IO.h"

#include <RobotController.h>

BelevatorControl::BelevatorControl() {}

void BelevatorControl::lift_speed(double output) {
  for (auto motor : IO::get_instance()->belev_motors) motor->Set(output); // Set for all motors
}

void BelevatorControl::claw(bool open) {
  IO::get_instance()->intake_solenoids[0]->Set(open ? DoubleSolenoid::Value::kForward : DoubleSolenoid::Value::kOff);
}

void BelevatorControl::intake(double left, double right) {
  for (auto motor : IO::get_instance()->intake_motors_left) motor->Set(left);
  for (auto motor : IO::get_instance()->intake_motors_right) motor->Set(right);
}

void BelevatorControl::intake(double power) {
  intake(power, power);
}
