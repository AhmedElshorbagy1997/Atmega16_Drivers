/*
 * main.c
 *
 *  Created on: ??þ/??þ/????
 *      Author: Ahmed
 */

#include "timer0.h"

uint8 tick = 0;

void TIMER0_newTick(void)
{
	tick++;
}

int main(void)
{
	/* Set initial value for TCNT0 and OCR0 */
	g_initialCounter = 0;
	g_CTC_OCR0 = 250;
	/* Set PIN0 in Portc as output */
	DDRC |= (1<<PC0);
	/* Set the Call back function pointer in the Timer0 driver */
	TIMER0_setCallBack(TIMER0_newTick);
	/* Create configuration structure for Timer0 driver */
	Timer0_configType TIMER0_config = {CTC,NORMAL_OC0_DISCONNECTED,F_CPU_1024,CTC_INTERRUPT,g_CTC_OCR0};
	/* Initialize both the Timer0 driver */
	TIMER0_init(&TIMER0_config,g_initialCounter);
	SREG |= (1<<7);
	while(1)
	{
		if(tick == 2)
		{
			PORTC ^= (1<<PC0);
			tick = 0;
		}
	}
}
