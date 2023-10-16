// Goal is to send datas of the motors to Matlab

// Include the current library

// ??
// #ince:\DOSSIERS PERSOS\ETUDES\ecoles_ingenieurs\mines paris\formation\2A\MECATRO\electronique\code_arduino\TelemetryDemo2\TelemetryDemo2.inolude "MecatroUtils.h"

#include "MecatroUtils.h"

// Include the AS5600 library (for the encoders) and Sparkfun I2C Mux (for multiplexer)
#include "AS5600.h"
#include "SparkFun_I2C_Mux_Arduino_Library.h"

// Header for I2C communication
#include "Wire.h"

// Define the control loop period, in ms.
#define CONTROL_LOOP_PERIOD 5

// Define the Multiplexer pins corresponding to each encoder
#define LEFT_ENCODER_PIN 0
// #define RIGHT_ENCODER_PIN

QWIICMUX multiplexer;
AS5600 rightEncoder, leftEncoder;


void setup()
{
  // Setup serial communication with the PC - for debugging and logging.
  // 230400 is the fastest speed for bluetooth ; if using USB, you can go up to 
  // 1000000.
  Serial.begin(230400);

  // Initialize telemetry
  // With 3 variables
  unsigned int const nVariables = 3;
  String variableNames[nVariables] = {"raw angle", "cumulative position", "angular speed"};
  mecatro::initTelemetry(nVariables, variableNames);

  // // With 1 variable
  // unsigned int const nVariables = 1;
  // String variableNames[nVariables] = {"raw angle"};
  // mecatro::initTelemetry(nVariables, variableNames);

  // Start I2C communication
  Wire.begin();
  // Set I2C clock speed to 400kHz (fast mode)
  Wire.setClock(400000);

  // Init multiplexer
  if (!multiplexer.begin())
  {
    // Serial.println("Error: I2C multiplexer not found. Check wiring.");
  }
  else
  {
    bool isInit = true;
    // // Set multiplexer to use port RIGHT_ENCODER_PIN to talk to right encoder.
    // multiplexer.setPort(RIGHT_ENCODER_PIN);
    // rightEncoder.begin();
    // if (!rightEncoder.isConnected())
    // {
    //   Serial.println("Error: could not connect to right encoder. Check wiring.");
    //   isInit = false;
    // }
    // Set multiplexer to use port LEFT_ENCODER_PIN to talk to left encoder.
    multiplexer.setPort(LEFT_ENCODER_PIN);
    leftEncoder.begin();
    if (!leftEncoder.isConnected())
    {
      // Serial.println("Error: could not connect to left encoder. Check wiring.");
      isInit = false;
    }

    if (isInit)
    {
      // Configure motor control and feedback loop call.
      mecatro::configureArduino(CONTROL_LOOP_PERIOD);

      // Serial.println("Init done");
    }
  }
}

void loop()
{
  // Don't forget to call this, otherwise nothing will happen !
  // This function never returns, put all your code inside mecatro::controlLoop.
  // Inside mecatro::run(), sendTelemetry is called whenever the telemetryBuffer is filled
  mecatro::run();
}


// This function is called periodically, every CONTROL_LOOP_PERIOD ms.
// Put all your code here.
void mecatro::controlLoop()
{
  // Serial.println("Begin controlLoop");

  // Start left motor
  mecatro::setMotorDutyCycle(0.0, 0.5);

  // Set multiplexer to use port LEFT_ENCODER_PIN to talk to left encoder.
  multiplexer.setPort(LEFT_ENCODER_PIN);
  
  // Check magnet positioning - this is for debug purposes only and is not required in normal operation.
  if (leftEncoder.magnetTooStrong())
  {
    // Serial.print(" ; warning: magnet too close.");
  }
  if (leftEncoder.magnetTooWeak())
  {
    // Serial.print(" ; warning: magnet too far.");
  }
  // Serial.println();


  // Send data 
  mecatro::log(0, leftEncoder.rawAngle() * AS5600_RAW_TO_DEGREES);
  mecatro::log(1, leftEncoder.getCumulativePosition() * AS5600_RAW_TO_DEGREES);
  mecatro::log(2, leftEncoder.getAngularSpeed() * AS5600_RAW_TO_DEGREES);

  // Show data in serial monitor
  // Serial.println(leftEncoder.rawAngle() * AS5600_RAW_TO_DEGREES);
}

