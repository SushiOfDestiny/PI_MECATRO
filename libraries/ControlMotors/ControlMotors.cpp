/*
  ControlMotors.h - Library to control motors of the "bolide" robot.
*/

#include <Arduino.h>
#include "MecatroUtils.h"
#include "ControlMotors.h"

// functions must be used inside a controlLoop

// Assume mecatro::setMotorDutyCycle takes argument in [-1, 1] and reverse rotation if < 0

namespace controlmotors{
  void driveBot(float speedIntensity) // float const& ??
  {
    mecatro::setMotorDutyCycle(speedIntensity, speedIntensity);
  }

  void turnBot(int turnIntensity)
  {
    // pass +1 to order to turn right
    // -1 < turnIntensity < 1
    
    // Recall left (right) motor is number 0 (1)
    mecatro::setMotorDutyCycle(speedIntensity, -1 * speedIntensity);

  }

  void stopMotors()
  {
    mecatro::setMotorDutyCycle(0., 0.);
  }
}

