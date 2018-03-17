#include "Auto.h"
#include "Belev.h"
#include "IO.h"
#include "Starategies/MPStarategy.h"
#include "Starategies/AutoBelevStarategy.h"

#include <openrio/powerup/MatchData.h>
#include "curtinfrc/strategy/mp_strategy.h"

#if BADAUTO
#include "Starategies/BadAutoStarategy.h"
#endif

#include <iostream>

using namespace curtinfrc;
using namespace OpenRIO::PowerUp;

AutoControl::AutoControl(Drivetrain *_drive, BelevatorControl *_belev) {
  drive = _drive;
  belev = _belev;
}

void AutoControl::init() {
  scale = MatchData::OwnedSide::UNKNOWN;
}

void AutoControl::tick() {
  if (scale == MatchData::OwnedSide::UNKNOWN) {
    if ((scale = MatchData::get_owned_side(MatchData::GameFeature::SCALE)) != MatchData::OwnedSide::UNKNOWN) {
      near_switch = MatchData::get_owned_side(MatchData::GameFeature::SWITCH_NEAR);
      far_switch = MatchData::get_owned_side(MatchData::GameFeature::SWITCH_FAR);

      #if BADAUTO
        std::shared_ptr<Strategy> strat = nullptr;
        strat = std::make_shared<BadAutoStarategy>(drive);
        drive->strategy_controller().set_active(strat);

        std::cout << "IS BAD, BUT WE NOT DUN GOOFED" << std::endl;
      #else
        //std::make_shared<AutoBelevStarategy>(drive)
        std::shared_ptr<Strategy> belev_strat = nullptr, belev_Strat_2 = nullptr, strat = nullptr, strat_2 = nullptr;
        belev_strat = std::make_shared<AutoBelevStarategy>(belev, AutoBelevStarategy::component::Belevator, 1, 1500);
        belev_strat_2 = std::make_shared<AutoBelevStarategy>(belev, AutoBelevStarategy::component::Intake, -1, 1000);
        strat = MPStarategy::make_strat(drive, "d3_Rswitch");
        strat_2 = std::make_shared<ExternalStarategy>(belev->strategy_controller, belev_strat_2);
        drive->strategy_controller().set_active(strat);
        drive->strategy_controller().append(strat_2);
        belev->strategy_controller().set_active(belev_strat);

        std::cout << "WE NOT DUN GOOFED" << std::endl;
      #endif
    }
  } else {
    // Do Something?
  }
}
