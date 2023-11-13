/*
  ControlMotors.h - Library to control motors of the "bolide" robot.
*/

#include "Arduino.h"
#include "ControlMotors.h"
#include "MecatroUtils.h"

// functions must be used inside a controlLoop

// Assume mecatro::setMotorDutyCycle takes argument in [-1, 1] and reverse rotation if < 0

ControlMotors::ControlMotors()
{

}

void ControlMotors::driveBot(float speedIntensity) // float const& ??
{
  mecatro::setMotorDutyCycle(speedIntensity, speedIntensity);
}

void ControlMotors::turnBot(int turnIntensity)
{
  // pass +1 to order to turn right
  // -1 < turnIntensity < 1
  
  // Recall left (right) motor is number 0 (1)
  mecatro::setMotorDutyCycle(speedIntensity, -1 * speedIntensity);

}

void ControlMotors::stopMotors()
{
  mecatro::setMotorDutyCycle(0., 0.);
}

