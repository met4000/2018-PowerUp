#pragma once

#include "curtinfrc/strategy/strategy.h"

using namespace curtinfrc;

class WaitStarategy : public Strategy {
public:
  WaitStarategy(int _t) {
    t = _t;
  };
  void tick(double time) override;

private:
  int t;
};
