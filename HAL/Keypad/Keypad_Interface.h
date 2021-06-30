/*
 * Keypad_Interface.h
 *
 *  Created on: Sep 3, 2020
 *      Author: Omar Fahmy
 */

#ifndef _KEYPAD_INTERFACE_H_
#define _KEYPAD_INTERFACE_H_

#include "../../LIB/STD_TYPES.h"

/*
 * This keypad driver is applicable for any nxm keypad, where n and m are in the
 * range of 1 ~ 8. It is considered that all rows are connected on the same
 * port, consecutively one after another, and in an ascending order. Also, It is
 * considered that all columns are connected on the same port, consecutively one after
 * another, and in an ascending order. Rows and columns can be on different ports.
 * In case no switches are pressed, the returned value of row and column are 100.
 */


/**************************************************************************************/
/* 	 							FUNCTIONS PROTOTYPE	 					    		  */
/**************************************************************************************/

/**************************************************************************************/
/* Description: initializes keypad columns as outputs and rows as pulled-up inputs    */
/* Input      : Nothing                                                               */
/* Output     : Error Checking                                                        */
/**************************************************************************************/
extern u8 Keypad_U8Init(void);
/**************************************************************************************/

/**************************************************************************************/
/* Description: gets the indices of the pressed key. Returns 100 in pressedRow        */
/* and pressedColumn in case no key is pressed  									  */
/* Input      : constant pointer to a character - constant pointer to a character     */
/* Output     : Error checking                                                        */
/**************************************************************************************/
extern u8 Keypad_U8GetPressedKey(u8* const pressedRow, u8* const pressedColumn);
/**************************************************************************************/

#endif
