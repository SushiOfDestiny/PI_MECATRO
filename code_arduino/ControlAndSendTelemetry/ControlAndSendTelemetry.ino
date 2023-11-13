/******************************************************************************
Control Robot and Send datas.

Inspired from a Sparkfun example.
******************************************************************************/

// Includes
#include "MecatroUtils.h"

// Include the AS5600 library (for the encoders) and Sparkfun I2C Mux (for multiplexer)
#include "AS5600.h"
#include "SparkFun_I2C_Mux_Arduino_Library.h"

// Header for I2C communication
#include "Wire.h"
#include "sensorbar.h"

// Definitions
// Define the control loop period, in ms.
#define CONTROL_LOOP_PERIOD 5

// Define the Multiplexer pins corresponding to each encoder
#define LEFT_ENCODER_PIN 0
// #define RIGHT_ENCODER_PIN

//Define motor polarity for left and right side -- USE TO FLIP motor directions if wired backwards
#define RIGHT_WHEEL_POL 1
#define LEFT_WHEEL_POL 1

//Define the states that the decision making machines uses:
#define IDLE_STATE 0
#define READ_LINE 1
#define GO_FORWARD 2
#define GO_LEFT 3
#define GO_RIGHT 4

uint8_t state;

QWIICMUX multiplexer;
AS5600 rightEncoder, leftEncoder;

// Uncomment one of the four lines to match your SX1509's address
//  pin selects. SX1509 breakout defaults to [0:0] (0x3E).
const uint8_t SX1509_ADDRESS = 0x3E;  // SX1509 I2C address (00)
//const byte SX1509_ADDRESS = 0x3F;  // SX1509 I2C address (01)
//const byte SX1509_ADDRESS = 0x70;  // SX1509 I2C address (10)
//const byte SX1509_ADDRESS = 0x71;  // SX1509 I2C address (11)

SensorBar mySensorBar(SX1509_ADDRESS);


void setup()
{
  // Setup serial communication with the PC - for debugging and logging.
  Serial.begin(230400); // 230400 is the fastest speed for bluetooth ; if using USB, you can go up to 1000000.
  Serial.println("Program started.");
  Serial.println();

  // Initialize telemetry
  // With 3 variables
  unsigned int const nVariables = 6;
  String variableNames[nVariables] = {"left raw angle",
                                      "right raw angle", 
                                      "left cumulative position", 
                                      "right cumulative position", 
                                      "left angular speed", 
                                      "right angular speed"};

  mecatro::initTelemetry(nVariables, variableNames);

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
    // Set multiplexer to use port RIGHT_ENCODER_PIN to talk to right encoder.
    multiplexer.setPort(RIGHT_ENCODER_PIN);
    rightEncoder.begin();
    if (!rightEncoder.isConnected())
    {
      Serial.println("Error: could not connect to right encoder. Check wiring.");
      isInit = false;
    }
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
  
  // Init SensorBar
  //Default: the IR will only be turned on during reads.
  mySensorBar.setBarStrobe();
  //Other option: Command to run all the time
  //mySensorBar.clearBarStrobe();

  //Default: dark on light
  mySensorBar.clearInvertBits();
  //Other option: light line on dark
  //mySensorBar.setInvertBits();
  
  //Don't forget to call .begin() to get the bar ready.  This configures HW.
  uint8_t returnStatus = mySensorBar.begin();
  if(returnStatus)
  {
	  Serial.println("sx1509 IC communication OK");
  }
  else
  {
	  Serial.println("sx1509 IC communication FAILED!");
  }
  Serial.println();
  
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
  Serial.println("Begin controlLoop");

  // Use of state machine like in the Sparkfun example.
  uint8_t nextState = state;
  switch (state) {
  case IDLE_STATE:
    mecatro::setMotorDutyCycle(0., 0.);      // Stops both motors
    nextState = READ_LINE;
    break;
  case READ_LINE:
    if( mySensorBar.getDensity() < 7 )
    {
      nextState = GO_FORWARD;
      if( mySensorBar.getPosition() < -50 )
      {
        nextState = GO_LEFT;
      }
      if( mySensorBar.getPosition() > 50 )
      {
        nextState = GO_RIGHT;
      }
    }
    else
    {
      nextState = IDLE_STATE;
    }
    break;
  case GO_FORWARD:
    driveBot(0.5);
    nextState = READ_LINE;
    break;
  case GO_LEFT:
    turnBot(-.75);
    nextState = READ_LINE;
    break;
  case GO_RIGHT:
    turnBot(.75);
    nextState = READ_LINE;
    break;
  default:
    mecatro::setMotorDutyCycle(0., 0.);       // Stops both motors
    break;
  }
  state = nextState;

  // Retrieve datas from magnetic encoders
  // Try to send datas from left then from right encoder.

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
  // Send data from left encoders
  mecatro::log(0, leftEncoder.rawAngle() * AS5600_RAW_TO_DEGREES);
  mecatro::log(1, leftEncoder.getCumulativePosition() * AS5600_RAW_TO_DEGREES);
  mecatro::log(2, leftEncoder.getAngularSpeed() * AS5600_RAW_TO_DEGREES);

  // Set multiplexer to use port RIGHT_ENCODER_PIN to talk to right encoder.
  multiplexer.setPort(RIGHT_ENCODER_PIN);
  // Check magnet positioning - this is for debug purposes only and is not required in normal operation.
  if (rightEncoder.magnetTooStrong())
  {
    // Serial.print(" ; warning: magnet too close.");
  }
  if (rightEncoder.magnetTooWeak())
  {
    // Serial.print(" ; warning: magnet too far.");
  }
  // Serial.println();
  // Send data from right encoders
  mecatro::log(3, rightEncoder.rawAngle() * AS5600_RAW_TO_DEGREES);
  mecatro::log(4, rightEncoder.getCumulativePosition() * AS5600_RAW_TO_DEGREES);
  mecatro::log(5, rightEncoder.getAngularSpeed() * AS5600_RAW_TO_DEGREES);

}


// Drive functions
//When using driveBot( int16_t driveInput ), pass positive number for forward and negative number for backwards
//driveInput can be -255 to 255
void driveBot( int16_t driveInput )
{
	int16_t rightVar;
	int16_t leftVar;
	rightVar = driveInput * RIGHT_WHEEL_POL;
	leftVar = -1 * driveInput * LEFT_WHEEL_POL;

  // Recall left (right) motor is number 0 (1)
	mecatro::setMotorDutyCycle(leftVar, rightVar);
	
}

//When using turnBot( float turnInput ), pass + for spin right.
//turnInput can be -1 to 1, where '1' means spinning right at max speed
void turnBot( float turnInput )
{
	int16_t rightVar;
	int16_t leftVar;
	//If turn is positive
	if( turnInput > 0 )
	{
		rightVar = -1 * 255 * RIGHT_WHEEL_POL * turnInput;
		leftVar = -1 * 255 * LEFT_WHEEL_POL * turnInput;
	}
	else
	{
		rightVar = 255 * RIGHT_WHEEL_POL * turnInput * -1;
		leftVar = 255 * LEFT_WHEEL_POL * turnInput * -1;
	}

	// Recall left (right) motor is number 0 (1)
	mecatro::setMotorDutyCycle(leftVar, rightVar);
	delay(5);
	
}

// *** Unused ***
//When using ( int16_t driveInput, float turnInput ), pass + for forward, + for right
//driveInput can be -255 to 255
//turnInput can be -1 to 1, where '1' means turning right, right wheel stopped
void driveTurnBot( int16_t driveInput, float turnInput )
{
	int16_t rightVar;
	int16_t leftVar;
	//if driveInput is negative, flip turnInput
	if( driveInput < 0 )
	{
		turnInput *= -1;
	}
	
	//If turn is positive
	if( turnInput > 0 )
	{
		rightVar = driveInput * RIGHT_WHEEL_POL * ( 1 - turnInput );
		leftVar = -1 * driveInput * LEFT_WHEEL_POL;
	}
	else
	{
		rightVar = driveInput * RIGHT_WHEEL_POL;
		leftVar = -1 * driveInput * LEFT_WHEEL_POL * (1 - ( turnInput * -1));
	}

	mecatro::setMotorDutyCycle(leftVar, rightVar);
  delay(5);
		
}