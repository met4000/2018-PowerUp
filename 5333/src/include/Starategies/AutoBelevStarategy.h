#pragma once

#include "curtinfrc/strategy/AutoStrategy.h"

#include "../Belev.h"

using namespace curtinfrc;

class AutoBelevStarategy : public AutoStrategy {
public:
  enum components {
    Belevator,
    Intake,
    Claw
  };

  using AutoStrategy::AutoStrategy;

  void start() override;
  void stop() override;

private:
  std::shared_ptr<BelevatorControl> component;
};
