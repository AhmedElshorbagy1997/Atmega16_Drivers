/*
 * timer0.c
 *
 *  Created on: ??þ/??þ/????
 *      Author: Ahmed
 */


#include "timer2.h"

/*******************************************************************************
 *                           Global Variables                                  *
 *******************************************************************************/

static volatile void (*g_callBackPtr)(void) = NULL_PTR;

uint8 g_initialCounter = 0;
uint8 g_CTC_OCR2       = 0;

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

void TIMER2_init(Timer2_configType * config_Ptr , uint8 a_initialCounter)
{
	if((config_Ptr->CTC_Mode) == SET_OC2 || (config_Ptr->CTC_Mode) == TOGGLE_OC2 || (config_Ptr->CTC_Mode) == CLEAR_OC2 )
	{
		SET_BIT(DDRD,PB7); // OC0 Pin as output pin
	}

	/* Timer initial value */
	TCNT2 = a_initialCounter;
	/* Choose Which Interrupt To Enable
	 * 0x01 for Overflow Interrupt
	 * 0x02 for CTC Interrupt
     */
	OCR2 = config_Ptr->CTC_Value;
	TIMSK = (TIMSK & 0x3F) | ((config_Ptr->Enable_Interrupt) << 6);
	/* FOC0 = 1 in non-PWM mode */
	SET_BIT(TCCR2,FOC2);
	/*
	 * insert the required clock value in the first three bits (CS10, CS11 and CS12)
	 * of TCCR0 Register
	 */
	TCCR2 = (TCCR2 & 0xF8) | ((config_Ptr->Clcok) & 0x07);
	/*
	 * insert the required CTC mode in bit no. 4,5 (COM00 and COM01)
	 * of TCCR0 Register
	 */
	TCCR2 = (TCCR2 & 0xCF) | ((config_Ptr->CTC_Mode) << 4);
	/*
	 * insert the required Waveform Generation mode in bit no. 3,6 (WGM00 and WGM01)
	 * of TCCR0 Register
	 */
	TCCR0 |= (((config_Ptr->Mode) & 0x01)<<WGM20) | ((((config_Ptr->Mode) & 0x02) >> 1) << WGM21);
}

void TIMER2_setCallBack(void (*a_ptr)(void))
{
	/* Save the address of the Call back function in a global variable */
	g_callBackPtr = a_ptr;
}

