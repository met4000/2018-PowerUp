#include "Starategies/ExternalStarategy.h"

#include <iostream>

void ExternalStarategy::start() {
  std::cout << "External" << std::endl;
  controller->append(strat);

  this->done = true;
}
