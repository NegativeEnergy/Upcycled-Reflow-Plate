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
*/

#include <PID_v1.h>
#include "Adafruit_MAX31855.h"
#include <LiquidCrystal.h>
#include <SPI.h>


//PIN DEFINITIONS -----------------------------------------------------------
//Thermocouple
#define MAXDO	3
#define MAXCS	4
#define MAXCLK	5
//LCD
#define LCDEN
#define LCDRS
#define D4LCD
#define D5LCD
#define D6LCD
#define D7LCD
//Relay
#define RELAY_PIN
//Fan
#define FANPIN

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
  // put your setup code here, to run once:

}

void loop() {
  // put your main code here, to run repeatedly:

}
