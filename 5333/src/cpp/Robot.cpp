// Shared headers
#include "curtinfrc/math.h"
#include "curtinfrc/drivetrain.h"
#include "curtinfrc/strategy/mp_strategy.h"
#include "WPILib.h"

// Robot part classes
#include "IO.h"
#include "Belev.h"
#include "Map.h"
#include "ControlMap.h"
#include "Auto.h"

// Starategies
#include "Starategies/AutoBelevStarategy.h"
#include "Starategies/BelevStarategy.h"
#include "Starategies/DriveStarategy.h"
#include "Starategies/ExternalStarategy.h"
#include "Starategies/IntakeStarategy.h"
#include "Starategies/TurnStarategy.h"
#include "Starategies/WaitStarategy.h"

// Other required libraries
#include <string>
#include <SmartDashboard/SmartDashboard.h>
#include <SmartDashboard/SendableChooser.h>
#include <iostream>
#include <stdint.h>
#include <cmath>

using namespace frc; // WPILib classes/functions
using namespace std;

class Robot : public TimedRobot {
public:
  Drivetrain *drive;
  BelevatorControl *belev;
  IO *io;

  AutoControl *auto_;
  unique_ptr<int> autoNum;
  SendableChooser<int*> chooser;

  Robot() { }

  void RobotInit() {
    chooser.AddDefault("Bad Auto", new int(0));
    chooser.AddObject("Auto A", new int(1));
    chooser.AddObject("Auto B", new int(2));
    SmartDashboard::PutData("Auto Modes", &chooser);

    try {
      CameraServer::GetInstance()->StartAutomaticCapture(0);
    } catch (...) {
      cout << "Front Camera failed to start" << endl;
    }

    try {
      CameraServer::GetInstance()->StartAutomaticCapture(1);
    } catch (...) {
      cout << "Rear Camera failed to start" << endl;
    }

    io = IO::get_instance(); // Refer to IO
    drive = new Drivetrain(io->left_motors[0], io->right_motors[0], io->left_motors[0], io->right_motors[0]);
    belev = new BelevatorControl();

    auto_ = new AutoControl(drive, belev);

    io->shifter_solenoid->Set(DoubleSolenoid::Value::kForward);
  }

  void AutonomousInit() {
    // belev->strategy_controller().set_active(make_shared<AutoBelevStarategy>(belev, AutoBelevStarategy::component::Claw, 0));
    // belev->strategy_controller().append(make_shared<WaitStarategy>(1000));
    // belev->strategy_controller().append(std::make_shared<AutoBelevStarategy>(belev, AutoBelevStarategy::component::Belevator, 0.8, 1800));
    // belev->strategy_controller().append(
    //   std::make_shared<ExternalStarategy>(belev->strategy_controller, std::make_shared<AutoBelevStarategy>(belev, AutoBelevStarategy::component::Claw, 1))
    // );

    // cout << "Auto Init" << endl;
    //
    // autoNum.reset(chooser.GetSelected());
    //
    // if (autoNum.get() != nullptr) {
    //   switch (*autoNum) {
    //   case 0:
    //     break;
    //
    //   case 1:
    //     break;
    //
    //   case 2:
    //     break;
    //   }
    // }
    //
    auto_->init();
  }
  void AutonomousPeriodic() {
    // belev->strategy_controller().periodic();

    // if (autoNum.get() != nullptr) {
      auto_->tick();
    //   drive->log_write(); // Make this bit call only on mutates later *
    //   // belev->log_write();
    // } else {
    //   // drive->set_left(0);
    //   // drive->set_right(0);
    // }
  }

  void TeleopInit() {
    cout << "Teleop Init" << endl;
    ControlMap::init();

    auto drive_strat = std::make_shared<DriveStarategy>(drive);
    drive->strategy_controller().set_active(drive_strat);

    auto belev_strat = make_shared<BelevStarategy>(belev);
    belev->strategy_controller().set_active(belev_strat);
  }
  void TeleopPeriodic() {
    SmartDashboard::PutNumber("Yaw", io->navx->GetYaw());

    drive->strategy_controller().periodic();

    belev->strategy_controller().periodic();
    belev->tick();
    belev->claw(ControlMap::intake_claw_state());

    double intake_throttle = -0.5 * (IO::get_instance()->right_joy->GetRawAxis(3) - 1);
    double intake_min = 0.75;
    belev->intake(ControlMap::intake_motor_power() * ((intake_min) + (1 - intake_min) * intake_throttle));
    SmartDashboard::PutNumber("Intake Throttle", intake_throttle);
  }

  void TestInit() {
    auto strat = std::make_shared<TurnStarategy>(drive, 90, 0.5);
    drive->strategy_controller().set_active(strat);
  }

  void TestPeriodic() {
    drive->strategy_controller().periodic();
  }
};

START_ROBOT_CLASS(Robot)
