/*
 * timer0.c
 *
 *  Created on: ??þ/??þ/????
 *      Author: Ahmed
 */


#include "timer0.h"

/*******************************************************************************
 *                           Global Variables                                  *
 *******************************************************************************/

static volatile void (*g_callBackPtr)(void) = NULL_PTR;

uint8 g_initialCounter = 0;
uint8 g_CTC_OCR0       = 0;

/*******************************************************************************
 *                       Interrupt Service Routines                            *
 *******************************************************************************/

ISR(TIMER0_OVF_vect)
{
	if(g_callBackPtr != NULL_PTR)
	{
		/* Call the Call Back function in the application after the edge is detected */
		(*g_callBackPtr)(); /* another method to call the function using pointer to function g_callBackPtr(); */
	}
}

ISR(TIMER0_COMP_vect)
{
	TCNT0 = g_initialCounter;
	if(g_callBackPtr != NULL_PTR)
	{
		/* Call the Call Back function in the application after the edge is detected */
		(*g_callBackPtr)(); /* another method to call the function using pointer to function g_callBackPtr(); */
	}
}

/*******************************************************************************
 *                      Functions Definitions                                  *
 *******************************************************************************/

void TIMER0_init(Timer0_configType * config_Ptr , uint8 a_initialCounter)
{
	if((config_Ptr->CTC_Mode) == SET_OC0 || (config_Ptr->CTC_Mode) == TOGGLE_OC0 || (config_Ptr->CTC_Mode) == CLEAR_OC0 )
	{
		SET_BIT(DDRB,PB3); // OC0 Pin as output pin
	}

	/* Timer initial value */
	TCNT0 = a_initialCounter;
	/* Choose Which Interrupt To Enable
	 * 0x01 for Overflow Interrupt
	 * 0x02 for CTC Interrupt
     */
	OCR0 = config_Ptr->CTC_Value;
	TIMSK = (TIMSK & 0xFC) | ((config_Ptr->Enable_Interrupt));
	/* FOC0 = 1 in non-PWM mode */
	SET_BIT(TCCR0,FOC0);
	/*
	 * insert the required clock value in the first three bits (CS10, CS11 and CS12)
	 * of TCCR0 Register
	 */
	TCCR0 = (TCCR0 & 0xF8) | ((config_Ptr->Clcok) & 0x07);
	/*
	 * insert the required CTC mode in bit no. 4,5 (COM00 and COM01)
	 * of TCCR0 Register
	 */
	TCCR0 = (TCCR0 & 0xCF) | ((config_Ptr->CTC_Mode) << COM00);
	/*
	 * insert the required Waveform Generation mode in bit no. 3,6 (WGM00 and WGM01)
	 * of TCCR0 Register
	 */
	TCCR0 |= (((config_Ptr->Mode) & 0x01)<<WGM00) | ((((config_Ptr->Mode) & 0x02) >> 1) << WGM01);
}

void TIMER0_setCallBack(void (*a_ptr)(void))
{
	/* Save the address of the Call back function in a global variable */
	g_callBackPtr = a_ptr;
}

