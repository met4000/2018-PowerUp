#include "Starategies/ExternalStarategy.h"

void ExternalStarategy::start() {
  controller->append(strat);

  this->done = true;
}
