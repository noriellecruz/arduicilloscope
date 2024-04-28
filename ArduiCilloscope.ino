#include <EEPROM.h>

#include <Adafruit_GFX.h> 
// needs to be Adafruit GFX Library v1.1.4, check/change your installed version
// otherwise you will get a black screen or compiler errors

#include "src/TFTLib/Adafruit_TFTLCD_8bit_STM32.h"
#include "global.h"
#include "variables.h"


#define FIRMWARE_VERSION	"1.0"

// ------------------------
void setup()	{
// ------------------------
	
 	afio_cfg_debug_ports(AFIO_DEBUG_NONE); //added to disable the debug port. 
	
	DBG_INIT(SERIAL_BAUD_RATE);
	DBG_PRINT("Dual channel oscilloscope with two logic channels, ver: ");
	DBG_PRINTLN(FIRMWARE_VERSION);

	// set digital and analog stuff
	initIO();
	
	// load scope config or factory reset to defaults
	loadConfig(digitalRead(BTN4) == LOW);
	
	// init the IL9341 display
	initDisplay();
}



// ------------------------
void loop()	{
// ------------------------
	controlLoop();
}
