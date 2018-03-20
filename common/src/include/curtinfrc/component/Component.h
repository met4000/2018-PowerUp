#pragma once

#include "curtinfrc/strategy/strategy.h"

namespace curtinfrc {
  class Component {
  public:
    virtual void tick();

    curtinfrc::StrategyController &strategy_controller() {
      return strat_controller;
    };

  private:
    curtinfrc::StrategyController strat_controller;
  };
} // ns curtinfrc
