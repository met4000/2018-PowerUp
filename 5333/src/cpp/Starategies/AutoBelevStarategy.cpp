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
    component->lift(power);
    break;

  case Intake:
    component->intake(power);
    break;

  case Claw:
    component->claw(power >= 0.5);
    break;
  }
}

void AutoBelevStarategy::stop() {
  switch (part) {
  case Belevator:
    component->lift(0);
    break;

  case Intake:
    component->intake(0);
    break;
  }
}
