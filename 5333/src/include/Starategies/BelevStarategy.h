#pragma once

#include "curtinfrc/motors/CurtinTalonSRX.h"
#include "curtinfrc/strategy/strategy.h"

#include "../Map.h"
#include "../Belev.h"

using namespace curtinfrc;

class BelevStarategy : public Strategy {
public:
  BelevStarategy(std::shared_ptr<BelevatorControl> _belev);
  void start() override;
  void tick(double time) override;
  void stop() override;

private:
  std::shared_ptr<BelevatorControl> belev;
};
