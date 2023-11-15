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
//#include "controllers.h"
#include "derivative.h"

// Define the control loop period, in ms.
#define CONTROL_LOOP_PERIOD 5
// Define the Multiplexer pins corresponding to each encoder
QWIICMUX multiplexer;
#define LEFT_ENCODER_PIN 3
#define RIGHT_ENCODER_PIN 2
AS5600 rightEncoder, leftEncoder;
// Set sensorbar communication
#define SENSORBAR_PORT 0
const uint8_t SX1509_ADDRESS = 0x3E;  // SX1509 I2C address (00)
SensorBar mySensorBar(SX1509_ADDRESS);  


// CONSTANTS
const double deltaT = CONTROL_LOOP_PERIOD * 1e-3;

// VARIABLES
double phiBar;
double phiLBar;
double phiRBar;
double phiSBar;
double phiDBar;

double phiLCurrent;

double phiRCurrent;

double DeltaPhiSumCurrent;
double DeltaPhiSumPrevious;

double DeltaPhiDifCurrent;
double DeltaPhiDifPrevious;

double position;
double cLFCurrent;
double cLFPrevious;

double etaSumCurrent;
double etaSumPrevious;

double etaDifCurrent;
double etaDifPrevious;

double DeltaPhiSumDot;
double DeltaPhiDifDot;

double deltacLF;
double deltacLFDot;

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

    //USum = Usbar + h1 * (DeltaPhiSumCurrent - Tds * DeltaPhiSumDot);
    Serial.println();
    Serial.println(Usbar);
    Serial.println(h2);
    // Start I2C communication
    Wire.begin();
    // Set I2C clock speed to 400kHz (fast mode)
    Wire.setClock(400000);

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
        Serial.println("Error: could not connect to right encoder. Check wiring.");
        isMultipInit = false;
        }
        //Set multiplexer to use port LEFT_ENCODER_PIN to talk to left encoder.
        multiplexer.setPort(LEFT_ENCODER_PIN);
        leftEncoder.begin();
        if (!leftEncoder.isConnected())
        {
        Serial.println("Error: could not connect to left encoder. Check wiring.");
        isMultipInit = false;
        }
    }
    multiplexer.setPort(SENSORBAR_PORT);
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
        phiLBar = leftEncoder.rawAngle() * AS5600_RAW_TO_DEGREES;
        phiRBar = rightEncoder.rawAngle() * AS5600_RAW_TO_DEGREES;
        phiSBar = phiLBar + phiRBar;
        phiDBar = phiRBar - phiLBar;
        // Configure motor control and feedback loop call.
        mecatro::configureArduino(CONTROL_LOOP_PERIOD);

        Serial.println("Init done");
        }

    // Initialize LED (for error logging)
    pinMode(LED_BUILTIN, OUTPUT);

    // Initialize previous variables for filtered derivatives
    Ur = Urbar;
    Ul = Ulbar;
    multiplexer.setPort(SENSORBAR_PORT);
    position = mySensorBar.getPosition();
    cLFCurrent = positionTocLF(position);
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
      mecatro::setMotorDutyCycle(0.0, 0.0);
      /*
      if (deltacLF > 0) {
        // Line is at left of robot
        mecatro::setMotorDutyCycle(USum/4, -1.0);
      }
      else {
        // Line is at right of robot
        mecatro::setMotorDutyCycle(1.0, -USum/4);
      }
      Serial.println("Density < 1");
      */
    }
    else{

        // Retrieve Angular Datas
        // Set multiplexer to use port LEFT_ENCODER_PIN to talk to left encoder.
        /*
        multiplexer.setPort(LEFT_ENCODER_PIN);
        phiLCurrent = leftEncoder.getCumulativePosition() * AS5600_RAW_TO_DEGREES;

        // Set multiplexer to use port right_ENCODER_PIN to talk to right encoder.
        multiplexer.setPort(RIGHT_ENCODER_PIN);
        phiRCurrent = rightEncoder.getCumulativePosition() * AS5600_RAW_TO_DEGREES;

        // Conversion into delta with ref in Sum,Diff base
        time = micros() / 1e6;
        DeltaPhiSumCurrent = phiRCurrent + phiLCurrent - (phiSBar + controllers::phiSumRef(time));
        DeltaPhiDifCurrent = phiRCurrent - phiLCurrent - phiLBar;
        */

        multiplexer.setPort(SENSORBAR_PORT);
        position = mySensorBar.getPosition();
        cLFPrevious = cLFCurrent;
        cLFCurrent = positionTocLF(position);
        deltacLF = cLFCurrent - cLFRef; 

        /*
        etaSumCurrent = derivative::getFilteredDerivative(etaSumPrevious, DeltaPhiSumCurrent, DeltaPhiSumPrevious, 1/ns, deltaT);
        DeltaPhiSumDot = controllers::etaToDerivative(etaSumCurrent, DeltaPhiSumCurrent, 1/ns);
        USum = Usbar - h1 * DeltaPhiSumCurrent - h2* DeltaPhiSumDot; // PD controller
        */
        //Serial.println(DeltaPhiSumCurrent);
        //Serial.println(etaSumCurrent);
        //Serial.println(DeltaPhiSumDot);
        etaDifPrevious = etaDifCurrent;
        etaDifCurrent = derivative::getFilteredDerivative(etaDifPrevious, cLFCurrent, cLFPrevious, epsiloncLF, deltaT);
        deltacLFDot = derivative::etaToDerivative(etaDifCurrent, deltacLF, epsiloncLF);
        UDif = kcLF*deltacLF + kcLFDot*deltacLFDot; // PD controller
        USum = 16;
        // Convert into right, left base
        Ur = 0.5*(USum + UDif);
        Ul = 0.5*(USum - UDif);

        // Update motor orders
        // Assuming max voltage is 12V and that motordutycycle is proportional to voltage
        Serial.println(deltacLFDot);

        mecatro::setMotorDutyCycle(Ur/Umax, -Ul/Umax); // minus sign is because of the wiring

        // update previous variables
        DeltaPhiSumPrevious = DeltaPhiSumCurrent;
        DeltaPhiDifPrevious = DeltaPhiDifCurrent;
        etaSumPrevious = etaSumCurrent;
        etaDifPrevious = etaDifCurrent;
    }


}

double positionTocLF(double position){
    // Convert position given by SensorBar to y used in the mathematical control equations.
    double cLF = - position * deltaY;
    return cLF;
}

