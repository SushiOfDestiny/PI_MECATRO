/*
  ControlMotors.h - Library to control motors of the "bolide" robot.
*/

#ifndef ControlMotors_h
#define ControlMotors_h

#include "Arduino.h"

class ControlMotors

{

  public:

    ControlMotors();

    void driveBot(float speedIntensity);

    void turnBot(int turnIntensity);

    void stopMotors();

};

#endif