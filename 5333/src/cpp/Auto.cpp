#include "Auto.h"
#include "Belev.h"
#include "IO.h"
#include "Starategies/MPStarategy.h"
#include "Starategies/AutoBelevStarategy.h"
#include "Starategies/AutoDriveStarategy.h"
#include "Starategies/ExternalStarategy.h"
#include "Starategies/WaitStarategy.h"

#include <openrio/powerup/MatchData.h>
#include "curtinfrc/strategy/mp_strategy.h"

#include "Starategies/BadAutoStarategy.h"

#include <iostream>

using namespace curtinfrc;
using namespace OpenRIO::PowerUp;

AutoControl::AutoControl(Drivetrain *_drive, std::shared_ptr<BelevatorControl> _belev) {
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
        std::shared_ptr<Strategy> belev_strat = nullptr, belev_strat_0 = nullptr, belev_strat_1 = nullptr, belev_strat_2 = nullptr, strat = nullptr, strat_0 = nullptr, strat_01 = nullptr, strat_1 = nullptr, strat_2 = nullptr;
        // belev_strat_1 = std::make_shared<AutoBelevStarategy>(belev, AutoBelevStarategy::components::Intake, -1, 1000);
        strat = std::make_shared<BadAutoStarategy>(drive, 0.5, 500);
        strat_0 = std::make_shared<AutoDriveStarategy>(drive, -0.5, -0.5, 500);
        strat_01 = std::make_shared<WaitStarategy>(2500);
          //
        //
          // drive->strategy_controller().append(strat_2);
          // belev->strategy_controller().set_active(belev_strat);

        drive->strategy_controller().set_active(strat);
        drive->strategy_controller().append(strat_0);
        drive->strategy_controller().append(strat_01);
        if (near_switch == MatchData::OwnedSide::RIGHT) {
          belev_strat = std::make_shared<WaitStarategy>(1200);
          belev_strat_0 = std::make_shared<AutoBelevStarategy>(belev, AutoBelevStarategy::components::Belevator, 0.8, 1800);
          strat_1 = std::make_shared<BadAutoStarategy>(drive, 0.7, 2500);
          belev_strat_1 = std::make_shared<WaitStarategy>(3300);
          belev_strat_2 = std::make_shared<AutoBelevStarategy>(belev, AutoBelevStarategy::components::Claw, 1, 1000);
        } else {
          strat_1 = std::make_shared<AutoDriveStarategy>(drive, 0.8, 0.65, 3000);
        }

        if (strat_1 != nullptr) drive->strategy_controller().append(strat_1);
        if (belev_strat != nullptr) belev->strategy_controller().set_active(belev_strat);
        if (belev_strat_0 != nullptr) belev->strategy_controller().append(belev_strat_0);
        if (belev_strat_1 != nullptr) belev->strategy_controller().append(belev_strat_1);
        if (belev_strat_2 != nullptr) belev->strategy_controller().append(belev_strat_2);

        std::cout << "WE NOT DUN GOOFED" << std::endl;
      #endif
    }
  }

  drive->strategy_controller().periodic();
  belev->strategy_controller().periodic();
}
