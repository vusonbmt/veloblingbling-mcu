/**
 *  @brief
 *      Tests the hardware
 *      
 *  @file
 *      test.h
 *  @author
 *      Peter Schmid, peter@spyr.ch
 *  @date
 *      2014-02-07
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

#ifndef TEST_H_
#define TEST_H_

/*
 ** ===================================================================
 **  Method      :  test
 */
/**
 *  @brief
 *  	Test all output ports (automatic test mode)
 *  	
 *  Returns only if ESC key is pressed.
 */
/* ===================================================================*/
void test(void);


#endif /* TEST_H_ */
