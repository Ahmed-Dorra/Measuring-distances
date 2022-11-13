/******************************************************************************
 *
 * Project: Ultrasonic Ex
 *
 * File Name: APP.c
 *
 * Description: Exercise for testing our ultrasonic driver
 *
 * Author: Ahmed_Dorra
 *
 *******************************************************************************/

#include "ultrasonic.h"
#include "lcd.h"
#include <avr/io.h>

int main(void)
{
	SREG |= (1<<7);
	uint16 distance;
	LCD_init();
	LCD_sendCommand(LCD_CURSOR_OFF);
	LCD_displayString("distance =    cm");
	LCD_moveCursor(0 , 11);
	Ultrasonic_init();
	while(1)
	{

		distance = Ultrasonic_readDistance();
		if(distance<100)
		{
			LCD_intgerToString(distance);
			LCD_displayCharacter(' ');
		}
		else if(distance>=100)
		{
			LCD_intgerToString(distance);
		}
		LCD_moveCursor(0 , 11);
	}
}

