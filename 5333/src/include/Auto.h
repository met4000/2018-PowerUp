#pragma once

#define BADAUTO true

#include "curtinfrc/drivetrain.h"
#include <openrio/powerup/MatchData.h>

#include "Belev.h"

using namespace curtinfrc;
using namespace OpenRIO::PowerUp;

class AutoControl {
public:
  AutoControl(Drivetrain *_drive, BelevatorControl *_belev);
  void init();
  void tick();
private:
  MatchData::OwnedSide near_switch, scale, far_switch;
  Drivetrain *drive;
  BelevatorControl *belev;
};
