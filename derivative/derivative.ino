// Goal is to send datas of the motors to serial monitor

// Include the current library

#include "MecatroUtils.h"
#include "derivative.h"

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
AS5600 leftEncoder;

double xCurrent;
double xPrevious;
double phiPrevious;
double phiCurrent;
const double tau = 1.0/25.0;
const double deltaT = 0.005;
double omega;
uint32_t now;
uint32_t lastMeasurement;
double t = 0;

double getAffineCurrentValue(double a, double x, double b) {
  return (a*x + b);
}

double getUnfilteredDerivative(double psiPrevious, double psiCurrent, double deltaT) {
  return ((psiCurrent - psiPrevious)/deltaT);
}

void setup()
{
  // Setup serial communication with the PC - for debugging and logging.
  // 230400 is the fastest speed for bluetooth ; if using USB, you can go up to 
  // 1000000.
  Serial.begin(1000000);

  // Initialize telemetry
  unsigned int const nVariables = 3;
  String variableNames[nVariables] = {"raw angle", "angular speed", "filtered angular speed"};
  mecatro::initTelemetry(nVariables, variableNames);

  // Start I2C communication
  Wire.begin();
  // Set I2C clock speed to 400kHz (fast mode)
  Wire.setClock(400000);

  // Init multiplexer
  if (!multiplexer.begin())
  {
    //Serial.println("Error: I2C multiplexer not found. Check wiring.");
  }
  else
  {
    bool isInit = true;
    // // Set multiplexer to use port RIGHT_ENCODER_PIN to talk to right encoder.
    // multiplexer.setPort(RIGHT_ENCODER_PIN);
    // rightEncoder.begin();
    // if (!rightEncoder.isConnected())
    // {
    //   isInit = false;
    // }
    // Set multiplexer to use port LEFT_ENCODER_PIN to talk to left encoder.
    multiplexer.setPort(LEFT_ENCODER_PIN);
    leftEncoder.begin();
    if (!leftEncoder.isConnected())
    {
      isInit = false;
    }

    if (isInit)
    {
      // Configure motor control and feedback loop call.
      mecatro::configureArduino(CONTROL_LOOP_PERIOD);
    }
  }

  // Initialize values for x_previous and phi_previous;
  multiplexer.setPort(LEFT_ENCODER_PIN);
  //phiCurrent = leftEncoder.getCumulativePosition() * AS5600_RAW_TO_DEGREES;
  phiCurrent = 0;
  xPrevious = 0;
  xCurrent = 0;
  now = micros();
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
  // Des tests à l'aide de la fonction micros() ont montré que la période variait légèrement (jusqu'à 1%)

  // Start left motor
  mecatro::setMotorDutyCycle(0.0, 0.1);

  // Set multiplexer to use port LEFT_ENCODER_PIN to talk to left encoder.
  multiplexer.setPort(LEFT_ENCODER_PIN);
  
  // Check magnet positioning - this is for debug purposes only and is not required in normal operation.
  if (leftEncoder.magnetTooStrong())
  {
    //Serial.print(" ; warning: magnet too close.");
  }
  if (leftEncoder.magnetTooWeak())
  {
    //Serial.print(" ; warning: magnet too far.");
  }

  // Get current values for phi and x
  /*
  phiPrevious = phiCurrent;
  phiCurrent = leftEncoder.getCumulativePosition() * AS5600_RAW_TO_DEGREES;
  xPrevious = xCurrent;
  xCurrent = getDerivative(xPrevious, phiPrevious, phiCurrent);
  omega = xCurrent + phiCurrent/tau;
  */

  lastMeasurement = now;
  now = micros();
  t++;
  phiPrevious = phiCurrent;
  phiCurrent = leftEncoder.getCumulativePosition() * AS5600_RAW_TO_DEGREES;
  xPrevious = xCurrent;
  xCurrent = derivative::getFilteredDerivative(xPrevious, phiPrevious, phiCurrent, tau, deltaT);
  omega = xCurrent + phiCurrent/tau;

  // Send data
  mecatro::log(0, leftEncoder.rawAngle() * AS5600_RAW_TO_DEGREES); // could use getCumulativePosition instead
  mecatro::log(1, leftEncoder.getAngularSpeed());
  mecatro::log(2, omega);

  // Print data
  /*
  Serial.print("Phi précédent : ");
  Serial.print(phiPrevious);
  Serial.print("  Phi courant : ");
  Serial.print(phiCurrent);
  Serial.print("  Omega : ");
  Serial.print(omega);
  Serial.println();
  */
  // Print calculated speeds
  /*
  Serial.print(leftEncoder.getAngularSpeed());
  Serial.print("Différence dérivées : ");
  Serial.print(leftEncoder.getAngularSpeed() - getUnfilteredDerivative(phiPrevious, phiCurrent, 0.005));
  Serial.println();
  */
}
