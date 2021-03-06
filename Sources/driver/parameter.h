/**
 *  @brief
 *  	Save and get configuration to the flash memory.
 *  	Save and get patterns (images) and scripts to the flash memory.
 *  	Log parameters to the flash memory (not used yet).
 *  	
 *		The internal FLASH memory is used to save persistently the parameters.
 *		128 KiB are reserved for the parameters.
 *		The standard FLASH memory for the program starts at 0x410 and
 *		end at 0x3FFFF (roughly 256 KiB, size 3FBF0)
 *		Now it ends at 0x24FFF.
 *
 *		The FLASH for the parameters starts at 0x25000 and ends at
 *		0x3FFFF (107 kiB). See also in the Kinetis Design Studio:
 *		Processor Expert Components
 *		CPU -> Build Options -> Generate linker file -> MemoryArea2
 *		-> Size 24BF0 [original 3FBF0])
 *		An erasable block has the size of 2 kiB (0x800).
 *
 *		The Flex NVM EEPROM is not used yet. Therefore  the EEPROM buffer RAM can
 *		be used for other purposes. It is used in display module for
 *		image_bufferP buffer. The 64 KiB Flash can be used for other purposes.
 *
 *		The Flex NVM 64 KiB Flash block is used for parameters and images now.
 *      
 *  @file
 *      parameter.c
 *  @author
 *      Peter Schmid, peter@spyr.ch
 *  @date
 *      2014-02-10
 *  @remark     
 *      Language: C, ProcessorExpert, GNU ARM Crosscompiler gcc-v4.2.0
 *  @copyright
 *      Peter Schmid, Switzerland
 *
 *      This file is part of "Velo Bling-Bling" main MCU firmware.
 *
 *		"Velo Bling-Bling" firmware is free software: you can redistribute it
 *		and/or modify it under the terms of the GNU General Public License as
 *		published by the Free Software Foundation, either version 3 of the
 *		License, or (at your option) any later version.
 *
 *		"Velo Bling-Bling" is distributed in the hope that it will be useful,
 *		but WITHOUT ANY WARRANTY; without even the implied warranty of
 *		MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 *		GNU General Public License for more details.
 *
 *		You should have received a copy of the GNU General Public License along
 *		with "Velo Bling-Bling". If not, see <http://www.gnu.org/licenses/>.
 */

#ifndef PARAMETER_H_
#define PARAMETER_H_

#include "definitions.h"
#include "visual/display.h"
#include "cyclo/cyclocomputer.h"

/**
**  @addtogroup parameter_module
**  @{
*/         

#define FLEX_NVM_RAM_BASE	0x14000000 		// Flex NVM EEPROM not used yet, 4 KiB EEE RAM available
#define FLEX_NVM_FLASH_BASE	0x10000000		// Flex NVM 64 KiB Flash block
#define FLASH_BASE_PARAM 0x25000			/**< where FLASH memory starts, see also protection region in Cpu Properties */

#define FLASH_BASE_ADR FLEX_NVM_FLASH_BASE	/**< flash base address for parameters and images */
#define FLASH_RECORD_VALID 0x55


typedef struct configParameter_s {
	/* configuration */
	double circumference;	
	
	/* mode & display */
	bool imperialUnits;
	double delay_front;		
	double between_front;
	double delay_rear;
	double between_rear;
	bool right;	
	bool front;
	double stretch;	
	int16_t blingStep;
	
	Display_modeT displayMode[BOTTOMSIDE+1][BLING+1];
	Cyclo_modeT cycloMode[BOTTOMSIDE+1][BLING+1];
	char String[BOTTOMSIDE+1][BLING+1][40];
	LED_colorT Color[BOTTOMSIDE+1][BLING+1];
	int Image [BOTTOMSIDE+1][BLING+1];

	int currScript;
	bool scriptExecution;

	/* cyclocomputer */
	double maxSpeed;
	double tripDistance;
	double totalDistance;
	double tripElevationGain;
	double totalElevationGain;
	double maxAltitude;
	double altimeterOffset;
	
	double tripTime;
	LDD_RTC_TTime watchTime;

	bool oledDebug;

	/* Hardware */
	bool slowHall_Present;
		
	uint8_t valid;			// if the config length change, the config is no longer valid
	
} configParameter_s;

/** log parameter is 12 bytes -> 80'000 k / 12 = 6666 Min > 110 h @ 1 S/Min */
typedef struct logParameter_s {
	float tripDistance;
	float altitude;
	float temperature;
} logParameter_s;


extern configParameter_s *configParameterP;		/**< points to the configParameter in the EEPROM */
bool FlashReady;								/**< as long as the FLASH process is ongoing this variable is false */ 

/*
 ** ===================================================================
 **  Method      :  flash_Init
 */
/**
 *  @brief
 *  	Initialises the Flash memory
 */
/* ===================================================================*/
void flash_Init();

/*
 ** ===================================================================
 **  Method      :  set_config
 */
/**
 *  @brief
 *  	copy the parameter to the configuration 
 */
/* ===================================================================*/
void set_config();

/*
 ** ===================================================================
 **  Method      :  set_params
 */
/**
 *  @brief
 *  	copy the configuration to the parameter
 */
/* ===================================================================*/
void set_params();

/*
 ** ===================================================================
 **  Method      :  save_params
 */
/**
 *  @brief
 *  	Saves the configuration parameters into the FLASH
 */
/* ===================================================================*/
void save_params();

/*
 ** ===================================================================
 **  Method      :  get_params
 */
/**
 *  @brief
 *  	Gets the configuration parameters from the FLASH
 */
/* ===================================================================*/
void get_params();

/*
 ** ===================================================================
 **  Method      :  clear_params
 */
/**
 *  @brief
 *  	Clears the configuration parameters into the FLASH
 */
/* ===================================================================*/
void clear_params();

/*
 ** ===================================================================
 **  Method      :  save_logdata
 */
/**
 *  @brief
 *  	Saves the log data parameters into the FLASH
 *  @param
 *  	param	Log data parameter to save to flash
 *  @param
 *  	record_nr	index for the parameter record
 *  	
 */
/* ===================================================================*/
void save_logdata(const int16 record_nr, logParameter_s *param);

/*
 ** ===================================================================
 **  Method      :  get_logdata
 */
/**
 *  @brief
 *  	Gets the log data parameters from the FLASH
 *  @param
 *  	param	Log data parameter to get from flash
 *  @param
 *  	record_nr	index for the parameter record
 */
/* ===================================================================*/
void get_logdata(const int16 record_nr, logParameter_s *param);

/*
 ** ===================================================================
 **  Method      :  erase_flash
 */
/**
 *  @brief
 *  	erases the internal FLASH
 */
/* ===================================================================*/
void erase_flash();

/*!
** @}
*/


#endif /* PARAMETER_H_ */
