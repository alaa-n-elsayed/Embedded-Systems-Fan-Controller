 /**************************************************************************************************
 *
 * [File Name]: Fan_Controller.c
 *
 * [Author]: Alaa Elsayed
 *
 * [Date Created]: 16 / 10 / 2021
 *
 * [Description]: Design a temperature-controlled fan using ATmega16 microcontroller,
 * 		   		  In which the fan is automatically turned ON or OFF according to the temperature.
 *
 ***************************************************************************************************/

#include "lcd.h"
#include "dc_motor.h"
#include "lm35_sensor.h"
#include "adc.h"

/* function main begins program execution */
int main(void)
{
	/********** Initialization Code **********/

	uint8 temp; /* Variable to store the result from the tempreture sensor */

	/*
	 * Initialize ADC Drive
	 */
	ADC_ConfigType configured_initialization = { INTERNAL, F_CPU_8 }; /* Create a configured structure to initialize ADC with */
	ADC_init(&configured_initialization); /* Initialize ADC by calling its init function */

	/*
	 * Initialize LCD Drive
	 */
	LCD_init(); /* Initialize LCD by calling its init function */

	/*
	 * Initialize DC Motor Driver
	 */
	DcMotor_Init(); /* Initialize DC Motor by calling its init function */

	/*
	 * Display ( Fan is .... ) only once at the first row of the LCD
	 */
	LCD_moveCursor(0,5); /* Move the cursor to the first row with suitable location */
	LCD_displayString("FAN is "); /* Display the message on LCD */

	/*
	 * Display ( Temp = .... C ) only once at the first row of the LCD
	 */
	LCD_moveCursor(1,5); /* Move the cursor to the second row with suitable location */
	LCD_displayString("Temp =    C"); /* Display the message on LCD */


	/* Super loop */
	for(;;)
	{
		/********** Application Code **********/

		temp = LM35_getTemperature(); /* Get the temperature from the sensor */

		/*
		 * Display the temperature every time at the same location
		 */

		LCD_moveCursor(1,13); /* Move the cursor to the second row with suitable location */


		if( temp >= 100 )
		{
			LCD_intgerToString( temp );
		}
		else
		{
			LCD_intgerToString( temp );

			/* In case the temp is three, two, or one number
			 * Print a space after the value to overwrite the previous digit in this location
			 */
			LCD_displayCharacter(' ');
		}


		/*
		 * Display the Fan state every time at the same location
		 * Change the motor speed depending on the temperature value
		 */

		LCD_moveCursor(0,12); /* Move the cursor to the first row with suitable location */

		if ( temp < 30 )
		{
            LCD_displayString("OFF");
			DcMotor_Rotate(OFF,0);      /* Turn off the motor and assign its speed to ZERO */
		}
		else if ( temp >= 30 && temp < 60 )
		{
			LCD_displayString("ON");
			LCD_displayCharacter(' ');
			DcMotor_Rotate(CW,25);      /* Turn on the motor with 25% of its speed */
		}
		else if ( temp >=60 && temp < 90 )
		{
			LCD_displayString("ON");
			DcMotor_Rotate(CW,50);      /* Turn on the motor with 50% of its speed */
		}
		else if ( temp >=90 && temp < 120 )
		{
			LCD_displayString("ON");
			DcMotor_Rotate(CW,75);      /* Turn on the motor with 75% of its speed */
		}
		else if ( temp >=120 )
		{
			LCD_displayString("ON");
			DcMotor_Rotate(CW,100);     /* Turn on the motor with 100% of its speed */
		}

	} /* end super loop */
} /* end function main */
