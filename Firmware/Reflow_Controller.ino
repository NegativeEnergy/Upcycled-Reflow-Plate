/* REFLOW CONTROLLER 
AUTHOR: GARRETT BRAINARD
TARGET DEVICE: TEENSY 3.1

---------------------- REQS ----------------------------------------------
    Need to include:
    LCD Library
    SD Card Library 
    Thermocouple Board: MAX31855
    */

/*To Do:
	Need to add SD Card profile managment
	Need to add Fan Control for heatsink. Start with Static
	Define function for buzzer start
	Define functon for buzzer stop
	Detect SD Card input
	Interrupt on reset pin
*/

#include <PID_v1.h>
#include "Adafruit_MAX31855.h"
#include <LiquidCrystal.h>
#include <SPI.h>


//PIN DEFINITIONS -----------------------------------------------------------
//Thermocouple
#define MAXDO 12 //input to microcontroller
#define MAXCS 10
#define MAXCLK 13
//LCD
#define LCDEN 16
#define LCDRS 17
#define D4LCD 18
#define D5LCD 19
#define D6LCD 20
#define D7LCD 21
//Relay
#define RELAY_PIN 22 //not sure I need PWM for this depends on PID library
//Fan
#define FANPIN 23
#define FANSENSE 3 //will need to use FreqMeasure Library Teensy
//SD
#define SDDIN 7 
#define SDDOUT 8 //input to microcontroller
#define SDCLK 14
#define SDCS 15
#define SDDET 1
//Reset
#define RESETPIN 0
//Buzzer - analog a14 12 bit analog output

//--------------------------------------------------------------------------

//INITIALIZE THERMOCOUPLE----------------------------------------------------
Adafruit_MAX31855 thermocouple(MAXCLK, MAXCS, MAXDO);

//reflow profile init --------------------------------------------------------
typedef struct profileValues_s {
  int16_t soakTemp;
  int16_t soakDuration;
  int16_t peakTemp;
  int16_t peakDuration;
  double  rampUpRate;
  double  rampDownRate;
  uint8_t checksum;
} Profile_t;

Profile_t activeProfile; // the one and only instance
int activeProfileId = 0;

//--------------------------------------------------------------------------


//State Machine -----------------------------------------------------------

typedef enum {
  None     = 0,
  Idle     = 1,
  Settings = 2,
  Edit     = 3,

  UIMenuEnd = 9,

  RampToSoak = 10,
  Soak,
  RampUp,
  Peak,
  RampDown,
  CoolDown,

  Complete = 20,

  Tune = 30
} State;


State currentState  = Idle;
State previousState = Idle;
bool stateChanged = false;
uint32_t stateChangedTicks = 0;

//------------------------------------------------------------------------


void setup() {
  //buzzer setup
  analogWriteResolution(12);

}

void loop() {
  // put your main code here, to run repeatedly:

}
