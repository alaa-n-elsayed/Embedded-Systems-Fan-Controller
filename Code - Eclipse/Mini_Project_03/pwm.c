 /******************************************************************************
 *
 * Module: PWM
 *
 * File Name: pwm.c
 *
 * Description: Source file for generating PWM from Timer0
 *
 * Author: Alaa Elsayed
 *
 *******************************************************************************/

#include <avr/io.h>
#include "pwm.h"
#include "gpio.h"

/*******************************************************************************
 *                      Functions Definitions                                  *
 *******************************************************************************/

void Timer0_PWM_Init(unsigned char set_duty_cycle)
{
	uint8 compare_value; /* Variable to store the compare value after modification */

	/*
	 * We get a number in range of ( 0 ->> 100 ) representing speed
	 * We will convert it to the equvilant one in duty cycle range ( 0 ->> 255 )
	 */
	compare_value = set_duty_cycle * 2.55;

	TCNT0 = 0; /* Set Timer0 initial value to 0 */

	OCR0 = compare_value; /* Set the Compare value */

	/* Configure OC0 Pin as output pin >> for generating the waves */
	GPIO_setupPinDirection(PORTB_ID, PIN3_ID, PIN_OUTPUT);

	/* Configure the timer control register
	 * 1. Fast PWM mode 								-> FOC0 = 0
	 * 2. CTC Mode  									-> WGM00 = 1 && WGM01 = 1
	 * 3. Toggle OC0 on compare match					-> COM00 = 0 && COM01 = 1
	 * 4. clock = F_CPU / 8								-> CS00 = 0  && CS01 = 1  && CS02 = 0
	 */
	TCCR0 |= ( 1 << WGM00 ) | ( 1 << WGM01 ) | ( 1 << COM01 ) | ( 1 << CS01 );
}
