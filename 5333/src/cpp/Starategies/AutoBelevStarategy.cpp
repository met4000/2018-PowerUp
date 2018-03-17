#include "Starategies/AutoBelevStarategy.h"

#include <iostream>
#include "WPILib.h"
#include "curtinfrc/PID.h"

#include "IO.h"
#include "ControlMap.h"
#include "Map.h"
#include "Belev.h"

void AutoBelevStarategy::start() {
  switch (part) {
  case Belevator:
    belev->lift(power);
    break;

  case Intake:
    belev->intake(power);
    break;

  case Claw:
    belev->claw(power >= 0.5);
    break;
  }
}

void AutoBelevStarategy::tick(double time) {
  if (time > t) this->done = true;
}

void AutoBelevStarategy::stop() {
  switch (part) {
  case Belevator:
    belev->lift(0);
    break;

  case Intake:
    belev->intake(0);
    break;

  case Claw:
    belev->claw(0);
    break;
  }
}
