#pragma once

#include "curtinfrc/strategy/strategy.h"


using namespace curtinfrc;

class ExternalStarategy : public Strategy {
public:
  ExternalStarategy(StrategyController *_controller, std::shared_ptr<Strategy> _strat) {
    controller = _controller;
    strat = _strat;
  };

  void start() override;
  void tick(double time) override {};

private:
  StrategyController *controller;
  std::shared_ptr<Strategy> strat;
};
