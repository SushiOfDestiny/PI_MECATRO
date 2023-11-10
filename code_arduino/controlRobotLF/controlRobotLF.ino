// Goal is to automatically programm the robot so that
// he follow the line
// at each loop, arduino must retrieve data, calculate desired tensions
// and order the motors with the right duty cycle.


#include "MecatroUtils.h"
#include "AS5600.h"
#include "SparkFun_I2C_Mux_Arduino_Library.h"
#include "Wire.h"
#include "sensorbar.h"
#include "constants.h"
#include "controllers.h"

// Define the control loop period, in ms.
#define CONTROL_LOOP_PERIOD 5
// Define the Multiplexer pins corresponding to each encoder
QWIICMUX multiplexer;
// Set sensorbar communication
const uint8_t SX1509_ADDRESS = 0x3E;  // SX1509 I2C address (00)
SensorBar mySensorBar(SX1509_ADDRESS);  


// CONSTANTS
const double deltaT = CONTROL_LOOP_PERIOD * 1e-3;

// VARIABLES
double phiLCurrent;

double phiRCurrent;

double DeltaPhiSumCurrent;
double DeltaPhiSumPrevious;

double DeltaPhiDifCurrent;
double DeltaPhiDifPrevious;

double position;
double cLFCurrent;

double etaSumCurrent;
double etaSumPrevious;

double etaDifCurrent;
double etaDifPrevious;

double DeltaPhiSumDot;
double DeltaPhiDifDot;

double deltacLF;

double USum;
double UDif;

double Ur;
double Ul;

double time;


void setup()
{
    // Setup serial communication with the PC - for debugging and logging.
    // 230400 is the fastest speed for bluetooth ; if using USB, you can go up to 
    // 1000000.
    Serial.begin(230400);

    // Start I2C communication
    Wire.begin();
    // Set I2C clock speed to 400kHz (fast mode)
    Wire.setClock(400000);

    bool isMultipInit = false;
    // Init multiplexer
    /*
    
    if (!multiplexer.begin())
    {
        Serial.println("Error: I2C multiplexer not found. Check wiring.");
    }
    else
    {
        isMultipInit = true;
    }
    */
    isMultipInit = true;

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

        Serial.println("Init done");
        }

    // Initialize LED (for error logging)
    pinMode(LED_BUILTIN, OUTPUT);

    // Initialize previous variables for filtered derivatives
    Ur = Urbar;
    Ul = Ulbar;

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
    // Retrieve position to line
    if( mySensorBar.getDensity() < 1 )
    // Line is not dark enough
    {
        // Robot stops
        mecatro::setMotorDutyCycle(0., 0.);
        digitalWrite(LED_BUILTIN, HIGH);  // turn the LED on (HIGH is the voltage level)
    }
    else{
        digitalWrite(LED_BUILTIN, LOW); // error logging purposes

        position = mySensorBar.getPosition();
        cLFCurrent = positionTocLF(position);
        deltacLF = cLFCurrent - cLFRef; 

        UDif = controllers::udPLF(deltacLF);
        USum = 3;
        // Convert into right, left base
        Ur = 0.5*(USum + UDif);
        Ul = 0.5*(USum - UDif);

        // Update motor orders
        // Assuming max voltage is 12V and that motordutycycle is proportional to voltage
        //Serial.println(Ur/Umax);
        //Serial.println(Ul/Umax);
        mecatro::setMotorDutyCycle(-Ur/Umax, -Ul/Umax); // minus sign is because of the wiring
    }


}

double positionTocLF(double position){
    // Convert position given by SensorBar to y used in the mathematical control equations.
    double cLF = - position * deltaY;
    return cLF;
}

