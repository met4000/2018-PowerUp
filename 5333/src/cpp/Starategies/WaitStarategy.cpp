#include "Starategies/WaitStarategy.h"

void WaitStarategy::tick(double time) {
  if (time > t) this->done = true;
}
