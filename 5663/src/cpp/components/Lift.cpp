#include "components/Lift.h"
#include <SmartDashboard/SmartDashboard.h>
using namespace components;

// Constructor for Lift class
Lift::Lift(int m1, int m2) {
  motor1 = new TalonSRX(m1);
  motor2 = new TalonSRX(m2);
  motor2->Set(ControlMode::Follower, m1);

  motor1->ConfigNominalOutputForward(0, 0);
	motor1->ConfigNominalOutputReverse(0, 0);
	motor1->ConfigPeakOutputForward(1, 0);
	motor1->ConfigPeakOutputReverse(-1, 0);
  motor1->Config_kF(0, 1023.0/topspeed, 10);
  motor1->Config_kP(0, 0.2, 10);
  motor1->Config_kI(0, 0, 10);
  motor1->Config_kD(0, 0, 10);
  motor1->ConfigMotionAcceleration(topspeed*4, 10);
  motor1->ConfigMotionCruiseVelocity(topspeed*5, 10);
  motor1->SetSensorPhase(true);
  motor1->SetSelectedSensorPosition(0, 0, 10);

  topSwitch = new DigitalInput(1);
  lowSwitch = new DigitalInput(0);
}

// Move lift to high position (for scale)
void Lift::SetHighPosition() {
  motor1->Set(ControlMode::PercentOutput, 0);
  motor1->Set(ControlMode::MotionMagic, highPosition);
  pos = 2;
  manualMode = false;
}

// Move lift to mid position (for switch)
void Lift::SetMidPosition() {
  motor1->Set(ControlMode::PercentOutput, 0);
  motor1->Set(ControlMode::MotionMagic, midPosition);
  pos = 1;
  manualMode = false;
}

// Move lift to low position
void Lift::SetLowPosition() {
  motor1->Set(ControlMode::PercentOutput, 0);
  motor1->Set(ControlMode::MotionMagic, 0);
  pos = 0;
  manualMode = false;
}

void Lift::Stop() {
  motor1->NeutralOutput();
}

// Set speed of Lift class motors
void Lift::SetSpeed(double speed) {
   if(fabs(speed) < deadzone) {
     speed = 0;
     if(manualMode) {
       //motor1->Set(ControlMode::PercentOutput, 0);
       if(flag) {
         motor1->Set(ControlMode::MotionMagic, motor1->GetSelectedSensorPosition(0));
         flag = false;
       }
     }
   } else {
     manualMode = true;
     flag = true;
     speed *= fabs(speed);
     if(lowSwitch->Get() && speed < 0) speed = 0;
     if(topSwitch->Get() && speed > 0) speed = 0;
     if(motor1->GetSelectedSensorPosition(0) < 4000 && speed < 0) speed *= 0.2;
     if(motor1->GetSelectedSensorVelocity(0) < -500 && motor1->GetSelectedSensorPosition(0) < 10000) speed = 0.05;
     if(motor1->GetSelectedSensorVelocity(0) > 800 && motor1->GetSelectedSensorPosition(0) > 22000) speed = 0.05;
     motor1->Set(ControlMode::PercentOutput, speed);
     pos = 3;
   }
 }

// Reset Lift class motor encoder
void Lift::ResetEncoder() {
  motor1->SetSelectedSensorPosition(0, 0, 10);
}

// Run periodic tasks
void Lift::RunPeriodic() {
  if(lowSwitch->Get() && motor1->GetSelectedSensorVelocity(0) > 0) ResetEncoder();
  if(motor1->GetSelectedSensorPosition(0) < 4000) motor1->ConfigPeakOutputReverse(-0.3, 0);
  else motor1->ConfigPeakOutputReverse(-1, 0);

  if(pos < lastpos) {
    motor1->ConfigMotionAcceleration(topspeed*2, 10);
    motor1->ConfigMotionCruiseVelocity(topspeed*2, 10);
    lastpos = pos;
  } else if(pos > lastpos) {
    motor1->ConfigMotionAcceleration(topspeed*4, 10);
    motor1->ConfigMotionCruiseVelocity(topspeed*5, 10);
    lastpos = pos;
  }

  SmartDashboard::PutNumber("Lift Encoder", motor1->GetSelectedSensorPosition(0));
  SmartDashboard::PutNumber("Lift Speed", motor1->GetSelectedSensorVelocity(0));
  SmartDashboard::PutBoolean("topSwitch", topSwitch->Get());
  SmartDashboard::PutBoolean("lowSwitch", lowSwitch->Get());
  SmartDashboard::PutNumber("Lift percent speed", motor1->GetMotorOutputPercent());
  SmartDashboard::PutBoolean("Manual Mode", manualMode);
  switch(pos) {
    case 0:
      SmartDashboard::PutString("Lift Position", "Low");
      break;
    case 1:
      SmartDashboard::PutString("Lift Position", "Mid");
      break;
    case 2:
      SmartDashboard::PutString("Lift Position", "High");
      break;
    default:
      SmartDashboard::PutString("Lift Position", "Manual");
      break;
  }
}
