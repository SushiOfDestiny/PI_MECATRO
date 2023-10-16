// Goal is to establish connection between Arduino, Mux and motors

#include "MecatroUtils.h"

// Header for I2C communication
#include "Wire.h"

// Define the control loop period, in ms.
#define CONTROL_LOOP_PERIOD 5


void setup() {
  // Setup serial communication with the PC - for debugging and logging.
  // 230400 is the fastest speed for bluetooth ; if using USB, you can go up to 
  // 1000000.
  Serial.begin(230400);

  // Configure motor control and feedback loop call.
  mecatro::configureArduino(CONTROL_LOOP_PERIOD);
}

void loop() {
  // Don't forget to call this, otherwise nothing will happen !
  // This function never returns, put all your code inside mecatro::controlLoop.
  // Inside mecatro::run(), sendTelemetry is called whenever the telemetryBuffer is filled
  mecatro::run();
}

// This function is called periodically, every CONTROL_LOOP_PERIOD ms.
// Put all your code here.
void mecatro::controlLoop()
{

}
