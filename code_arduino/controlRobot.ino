// Goal is to automatically programm the robot so that
// he follow the line
// at each loop, arduino must retrieve data, calculate desired tensions
// and order the motors with the right duty cycle.


#include "MecatroUtils.h"
// Include the AS5600 library (for the encoders) and Sparkfun I2C Mux (for multiplexer)
#include "AS5600.h"
#include "SparkFun_I2C_Mux_Arduino_Library.h"
// Header for I2C communication
#include "Wire.h"
// Header for Sensorbar communication
#include "sensorbar.h"
// Header for constants
#include "constants.h"
// Header for controlers
#include "controlers.h"

// Define the control loop period, in ms.
#define CONTROL_LOOP_PERIOD 5
// Define the Multiplexer pins corresponding to each encoder
#define LEFT_ENCODER_PIN 0
#define RIGHT_ENCODER_PIN 1

QWIICMUX multiplexer;
AS5600 rightEncoder, leftEncoder;


void setup()
{
    // Setup serial communication with the PC - for debugging and logging.
    // 230400 is the fastest speed for bluetooth ; if using USB, you can go up to 
    // 1000000.
    Serial.begin(230400);

    // Initialize telemetry
    unsigned int const nVariables = 2;
    String variableNames[nVariables] = {"right raw angle", ="left raw angle"};
    mecatro::initTelemetry(nVariables, variableNames);


    // Start I2C communication
    Wire.begin();
    // Set I2C clock speed to 400kHz (fast mode)
    Wire.setClock(400000);


    // Init multiplexers
    bool isMultipInit = false;
    if (!multiplexer.begin())
    {
        // Serial.println("Error: I2C multiplexer not found. Check wiring.");
    }
    else
    {
        isMultipInit = true;
        // Set multiplexer to use port RIGHT_ENCODER_PIN to talk to right encoder.
        multiplexer.setPort(RIGHT_ENCODER_PIN);
        rightEncoder.begin();
        if (!rightEncoder.isConnected())
        {
        // Serial.println("Error: could not connect to right encoder. Check wiring.");
        isMultipInit = false;
        }
        //Set multiplexer to use port LEFT_ENCODER_PIN to talk to left encoder.
        multiplexer.setPort(LEFT_ENCODER_PIN);
        leftEncoder.begin();
        if (!leftEncoder.isConnected())
        {
        // Serial.println("Error: could not connect to left encoder. Check wiring.");
        isMultipInit = false;
        }
    }

    // Set sensorbar communication
    const uint8_t SX1509_ADDRESS = 0x3E;  // SX1509 I2C address (00)
    SensorBar mySensorBar(SX1509_ADDRESS);  

    //Default: the IR will only be turned on during reads.
    mySensorBar.setBarStrobe();
    //Other option: Command to run all the time
    //mySensorBar.clearBarStrobe();

    //Default: dark on light
    mySensorBar.clearInvertBits();
    //Other option: light line on dark
    //mySensorBar.setInvertBits();

    //Don't forget to call .begin() to get the bar ready.  This configures HW.
    uint8_t isSensorInit = mySensorBar.begin();
    if(isSensorInit)
    {
        Serial.println("sx1509 IC communication OK");
    }
    else
    {
        Serial.println("sx1509 IC communication FAILED!");
    }
    Serial.println();

    // If Multip and Sensorbar are init, we configure Arduino
    if (isMultipInit && isSensorInit)
        {
        // Configure motor control and feedback loop call.
        mecatro::configureArduino(CONTROL_LOOP_PERIOD);

        // Serial.println("Init done");
        }

    // Initialize previous variables for filtered derivatives

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
    // Retrieve Angular Datas
    // Set multiplexer to use port LEFT_ENCODER_PIN to talk to left encoder.
    multiplexer.setPort(LEFT_ENCODER_PIN);
    double phil = leftEncoder.getCumulativePosition() * AS5600_RAW_TO_DEGREES;
    // Set multiplexer to use port right_ENCODER_PIN to talk to right encoder.
    multiplexer.setPort(RIGHT_ENCODER_PIN);
    double phir = rightEncoder.getCumulativePosition() * AS5600_RAW_TO_DEGREES;

    // Retrieve position to line
    if( mySensorBar.getDensity() > 7 )
    // Line is not dark enough
    {
        // Robot stops
        mecatro::setMotorDutyCycle(0., 0.);
    }
    else{
        double position;
        position = mySensorBar.getPosition();
        double cLF = positionTocLF(position);

        
        
    }


}

double positionTocLF(double position){
    // Convert position given by SensorBar to y used in the mathematical control equations.
    double cLF = - position * deltaY;
    return cLF;
}

