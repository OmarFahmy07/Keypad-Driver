/*
 * Keypad_Program.h
 *
 *  Created on: Sep 3, 2020
 *      Author: Omar Fahmy
 */

/* 		 LIB LAYER 			*/
#include "../../LIB/STD_TYPES.h"
#include "../../LIB/COMMON_MACROS.h"
/* 		 HAL LAYER 			*/
#include "Keypad_Configure.h"
#include "Keypad_Private.h"
/* 		 MCAL LAYER 		*/
#include "../../MCAL/DIO/DIO_Interface.h"
/* 		DELAY LIBRARY 		*/
#include <util/delay.h>

/***********************************************************************************/
/* 							PUBLIC FUNCTIONS IMPLEMENTATION						   */
/***********************************************************************************/

u8 Keypad_U8Init(void)
{
	/*	Check Correct Columns Configuration */
#if COLUMNS_PORT >= DIO_PORTA && COLUMNS_PORT <= DIO_PORTD
#if FIRST_COLUMN_PIN >= DIO_PIN0 && FIRST_COLUMN_PIN <= DIO_PIN7
#if NUMBER_OF_COLUMNS >= MIN_COLUMNS && NUMBER_OF_COLUMNS <= MAX_COLUMNS
#if FIRST_COLUMN_PIN + NUMBER_OF_COLUMNS <= MAX_INDEX
	/*	Check Correct Rows Configuration */
#if ROWS_PORT >= DIO_PORTA && ROWS_PORT <= DIO_PORTD
#if FIRST_ROW_PIN >= DIO_PIN0 && FIRST_ROW_PIN <= DIO_PIN4
#if NUMBER_OF_ROWS >= MIN_ROWS && NUMBER_OF_ROWS <= MAX_ROWS
#if FIRST_ROW_PIN + NUMBER_OF_ROWS <= MAX_INDEX
	/*	Configure columns as output	*/
	for (u8 LOC_U8Pin = FIRST_COLUMN_PIN; LOC_U8Pin < FIRST_COLUMN_PIN + NUMBER_OF_COLUMNS; LOC_U8Pin++)
	{
		DIO_U8SetPinDirection(COLUMNS_PORT, LOC_U8Pin, DIO_PIN_OUTPUT);
	}

	/*	Configure rows in pulled-up input mode */
	for (u8 LOC_U8Pin = FIRST_ROW_PIN; LOC_U8Pin < FIRST_ROW_PIN + NUMBER_OF_ROWS; LOC_U8Pin++)
	{
		DIO_U8SetPinDirection(ROWS_PORT, LOC_U8Pin, DIO_PIN_INPUT);
		DIO_U8SetPinValue(ROWS_PORT, LOC_U8Pin, DIO_PIN_HIGH);
	}

	return NO_ERROR;
#else
#error "Rows are not placed on the same port"
#endif
#else
#error "Incorrect number of rows"
#endif
#else
#error "Incorrect first row pin"
#endif
#else
#error "Incorrect rows' port"
#endif
#else
#error "Columns are not placed on the same port"
#endif
#else
#error "Incorrect number of columns"
#endif
#else
#error "Incorrect first column pin"
#endif
#else
#error "Incorrect columns' port"
#endif
	return NO_ERROR;
}

u8 Keypad_U8GetPressedKey(u8* const LOC_U8PressedRow, u8* const LOC_U8PressedColumn)
{
	if (LOC_U8PressedRow != NULL && LOC_U8PressedColumn != NULL)
	{
		/*	Set Columns initially to high	*/
		for (u8 LOC_U8Pin = FIRST_COLUMN_PIN; LOC_U8Pin < FIRST_COLUMN_PIN + NUMBER_OF_COLUMNS; LOC_U8Pin++)
		{
			DIO_U8SetPinValue(COLUMNS_PORT, LOC_U8Pin, DIO_PIN_HIGH);
		}

		/*	Loop over columns	*/
		for (u8 LOC_U8Column = FIRST_COLUMN_PIN; LOC_U8Column < FIRST_COLUMN_PIN + NUMBER_OF_COLUMNS; LOC_U8Column++)
		{
			/*	Activate column	*/
			DIO_U8SetPinValue(COLUMNS_PORT, LOC_U8Column, DIO_PIN_LOW);
			/*	Loop over rows	*/
			for (u8 LOC_U8Row = FIRST_ROW_PIN; LOC_U8Row < FIRST_ROW_PIN + NUMBER_OF_ROWS; LOC_U8Row++)
			{
				u8 LOC_U8Value;
				DIO_U8GetPinValue(ROWS_PORT, LOC_U8Row, &LOC_U8Value);
				/*	If key is pressed	*/
				if (DIO_PIN_LOW == LOC_U8Value)
				{
					/* To avoid bouncing on pressing */
					_delay_ms(10);

					/* Blocking - to avoid printing the same character multiple times */
					while (DIO_PIN_LOW == LOC_U8Value)
					{
						DIO_U8GetPinValue(ROWS_PORT, LOC_U8Row, &LOC_U8Value);
					}

					/* To avoid bouncing on releasing */
					_delay_ms(10);
					*LOC_U8PressedRow = LOC_U8Row - FIRST_ROW_PIN;
					*LOC_U8PressedColumn = LOC_U8Column - FIRST_COLUMN_PIN;
					return NO_ERROR;
				}
			}

			/*	Deactivate column	*/
			DIO_U8SetPinValue(COLUMNS_PORT, LOC_U8Column, DIO_PIN_HIGH);
		}

		/*	If control reaches here, then nothing was pressed	*/
		*LOC_U8PressedRow = NOTHING_PRESSED;
		*LOC_U8PressedColumn = NOTHING_PRESSED;
		return NO_ERROR;
	}
	else
	{
		return ERROR;
	}
}
