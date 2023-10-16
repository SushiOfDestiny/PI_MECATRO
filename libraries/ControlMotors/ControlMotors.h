/*
  ControlMotors.h - Library to control motors of the "bolide" robot.
*/

#include <Arduino.h>
#include "MecatroUtils.h"
#include "ControlMotors.h"

// functions must be used inside a controlLoop

// Assume mecatro::setMotorDutyCycle takes argument in [-1, 1] and reverse rotation if < 0

namespace controlmotors{
  void driveBot(float speedIntensity);

  void turnBot(int turnIntensity);

  void stopMotors();
};



