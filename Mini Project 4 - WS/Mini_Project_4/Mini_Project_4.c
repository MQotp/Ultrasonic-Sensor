/*
 * Mini_Project_4.c
 *
 *  Created on: Oct 14, 2022
 *      Author: Mahmoud Qotp
 */


#include "lcd.h"
#include "ultrasonic.h"
#include <avr/io.h>
#include <util/delay.h>

int main(void)
{
	uint16 distance = 0;
	LCD_init();
	Ultrasonic_init();
	SREG |= (1<<7);
	LCD_displayString("Distance=     cm");
	while(1)
	{
		distance = Ultrasonic_readDistance();
		LCD_moveCursor(0,10);
		LCD_intgerToString(distance);
		/* Check if the distance measure is going beyond the range */
		if(distance >= HCSR04_MODEL_MAXIMUM_RANGE)
		{
			LCD_displayStringRowColumn(1,0,"Invalid read.");
		}
		else
		{
			/* Check if the distance less than 1 m to display extra character to avoid screen residuals. */
			if(distance < 100)
			{
				LCD_displayCharacter(' ');
			}
			/* Check if the distance less than 10 cm to display 2 extra characters to avoid screen residuals. */
			else if(distance < 10)
			{
				LCD_displayCharacter(' ');
				LCD_displayCharacter(' ');
			}
			/* clear the second line in the valid range of the sensor. */
			LCD_displayStringRowColumn(1,0,"                ");
		}
		_delay_ms(1);
	}
}
