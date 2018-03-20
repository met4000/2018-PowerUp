#pragma once

#include "curtinfrc/strategy/strategy.h"
#include "curtinfrc/component/Component.h"

namespace curtinfrc {
  class AutoStrategy : public Strategy {
  public:
    explicit AutoStrategy(std::shared_ptr<Component> _component, int _part, double _power, int _t = 0) {
      component = _component;
      part = _part;    // Passed as enum, evaluated in start() and stop() with enum
      power = _power;
      t = _t;
    };

    virtual void start();
    void tick(double time) final {
      if (time > t) this->done = true;
    };
    virtual void stop();

  protected:
    std::shared_ptr<Component> component;
    int part;
    double power;

  private:
    int t;
  };
}
