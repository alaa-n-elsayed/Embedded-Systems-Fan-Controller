 /******************************************************************************
 *
 * Module: PWM
 *
 * File Name: pwm.h
 *
 * Description: header file for generating PWM from Timer0
 *
 * Author: Alaa Elsayed
 *
 *******************************************************************************/


#ifndef PWM_H_
#define PWM_H_

#include "std_types.h"
/*******************************************************************************
 *                      Functions Prototypes                                   *
 *******************************************************************************/

/* Description:
 * The function responsible for trigger the Timer0 with the PWM Mode.
 * Microcontroller will generate PWM with frequency ( 500 Hz )
 * F_CPU = 1 Mhz	//	Prescaler = 8
 * F_PWM = ( F_CPU ) / ( Prescaler * 256 ) = ( 1 * 10^6 ) / ( 8 * 256 ) 	---> 	F_PWM = 488.28 = 500 Hz
 * Compare Register value is sent by the DC Motor Driver to the Timer0_PWM_Init Function as Argument
 * Duty Cycle can be changed by updating the value in the Compare Register
 */
void Timer0_PWM_Init(unsigned char set_duty_cycle);

#endif /* PWM_H_ */
