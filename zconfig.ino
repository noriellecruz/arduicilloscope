// zconfig: since we are referencing variables defined in other files 

#define PREAMBLE_VALUE	2859


// ------------------------
void loadConfig(boolean reset)	{
// ------------------------
	DBG_PRINTLN("Loading stored config...");

	if(EEPROM.init() != EEPROM_OK)	{
		loadDefaults();
		return;
	}
	
	// read preamble
	if(reset || (EEPROM.read(PARAM_PREAMBLE) != PREAMBLE_VALUE))	{
		loadDefaults();
		formatSaveConfig();
		return;
	}	
	
	// load all the parameters from EEPROM
	uint16_t data;
	
	data = EEPROM.read(PARAM_TIMEBASE);
	setTimeBase(data);
	
	// trigger type is not persisted
	setTriggerType(TRIGGER_AUTO);

	data = EEPROM.read(PARAM_TRIGDIR);
	setTriggerRising(data == 1);
	
	data = EEPROM.read(PARAM_XCURSOR);
	xCursor = data;
	
	data = EEPROM.read(PARAM_YCURSOR);
	yCursors[0] = data;
	
	data = EEPROM.read(PARAM_YCURSOR + 1);
	yCursors[1] = data;
	
	data = EEPROM.read(PARAM_YCURSOR + 2);
	yCursors[2] = data;

	data = EEPROM.read(PARAM_YCURSOR + 3);
	yCursors[3] = data;

	data = EEPROM.read(PARAM_WAVES);
	waves[0] = data;
	
	data = EEPROM.read(PARAM_WAVES + 1);
	waves[1] = data;
	
	data = EEPROM.read(PARAM_WAVES + 2);
	waves[2] = data;
	
	data = EEPROM.read(PARAM_WAVES + 3);
	waves[3] = data;
	
	data = EEPROM.read(PARAM_TLEVEL);
	setTriggerLevel(data);
	
	printStats = EEPROM.read(PARAM_STATS);
	zeroVoltageA1 = EEPROM.read(PARAM_ZERO1);
	zeroVoltageA2 = EEPROM.read(PARAM_ZERO2);
	
	
	DBG_PRINTLN("Loaded config:");
	DBG_PRINT("Timebase: ");DBG_PRINTLN(currentTimeBase);
	DBG_PRINT("Trigger Rising: ");DBG_PRINTLN(triggerRising);
	DBG_PRINT("Trigger Type: ");DBG_PRINTLN(triggerType);
	DBG_PRINT("X Cursor Pos: ");DBG_PRINTLN(xCursor);
	DBG_PRINT("Y Cursors: ");DBG_PRINT(yCursors[0]);DBG_PRINT(", ");DBG_PRINT(yCursors[1]);DBG_PRINT(", ");DBG_PRINT(yCursors[2]);DBG_PRINT(", ");DBG_PRINTLN(yCursors[3]);
	DBG_PRINT("Waves: ");DBG_PRINT(waves[0]);DBG_PRINT(", ");DBG_PRINT(waves[1]);DBG_PRINT(", ");DBG_PRINT(waves[2]);DBG_PRINT(", ");DBG_PRINTLN(waves[3]);
	DBG_PRINT("Trigger Level: ");DBG_PRINTLN(data);
	DBG_PRINT("Print Stats: ");DBG_PRINTLN(printStats);
	DBG_PRINT("Wave1 Zero: ");DBG_PRINTLN(zeroVoltageA1);
	DBG_PRINT("Wave2 Zero: ");DBG_PRINTLN(zeroVoltageA2);
	
	// check if EEPROM left enough space, or else invoke formatSaveConfig
}



// ------------------------
void loadDefaults()	{
// ------------------------
	DBG_PRINTLN("Loading defaults");

	setTimeBase(T30US);
	setTriggerRising(true);
	setTriggerType(TRIGGER_AUTO);
	setTriggerLevel(0);
	
	// set x in the middle
	xCursor = (NUM_SAMPLES - GRID_WIDTH)/2;
 
	// set y in the middle
	yCursors[0] = -70;
	yCursors[1] = -90;
	yCursors[2] = -110;
	yCursors[3] = -130;
	
	// show all waves
	waves[0] = true;
	waves[1] = true;
	waves[2] = true;
	waves[3] = true;
	
	printStats = false;
	
	zeroVoltageA1 = 1985;
	zeroVoltageA2 = 1985;
}



// ------------------------
void formatSaveConfig()	{
// ------------------------
	DBG_PRINTLN("Formatting EEPROM");
	EEPROM.format();
	DBG_PRINTLN("Saving all config params....");
	
	saveParameter(PARAM_PREAMBLE, PREAMBLE_VALUE);
	
	saveParameter(PARAM_TIMEBASE, currentTimeBase);
	saveParameter(PARAM_TRIGDIR, triggerRising);
	saveParameter(PARAM_XCURSOR, xCursor);
	saveParameter(PARAM_YCURSOR, yCursors[0]);
	saveParameter(PARAM_YCURSOR + 1, yCursors[1]);
	saveParameter(PARAM_YCURSOR + 2, yCursors[2]);
	saveParameter(PARAM_YCURSOR + 3, yCursors[3]);
	
	saveParameter(PARAM_WAVES, waves[0]);
	saveParameter(PARAM_WAVES + 1, waves[1]);
	saveParameter(PARAM_WAVES + 2, waves[2]);
	saveParameter(PARAM_WAVES + 3, waves[3]);
	
	saveParameter(PARAM_TLEVEL, trigLevel);
 	saveParameter(PARAM_STATS, printStats);
	
	saveParameter(PARAM_ZERO1, zeroVoltageA1);
	saveParameter(PARAM_ZERO2, zeroVoltageA2);
}



// ------------------------
void saveParameter(uint16_t param, uint16_t data)	{
// ------------------------
	uint16 status = EEPROM.write(param, data);
	if(status != EEPROM_OK)	{
		DBG_PRINT("Unable to save param in EEPROM, code: ");DBG_PRINTLN(status);
	}
}


