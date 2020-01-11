/*
 * Mini_Project_2.c
 *
 *  Created on: 10/1/2020
 *      Author: Ahmed Mohamed Elshorbagy
 */


#include "adc.h"
#include "pwm.h"
#include "lcd.h"
#include "interrupt.h"

uint8 dir = 0;

/* Function will be served when rising edge come to INT1 pin
 * >> it will change the direction of motor
 */

void Reverse_Direction(void)
{
	if(dir == 0)
	{
		SET_BIT(PORTB,PB0);
		CLEAR_BIT(PORTB,PB1);
		dir = 1;
	}
	else if(dir == 1)
	{
		SET_BIT(PORTB,PB1);
		CLEAR_BIT(PORTB,PB0);
		dir = 0;
	}
}

int main(void)
{
	/* Set 0,1 bits output for motor */
	SET_BIT(DDRB,PB0);
	SET_BIT(DDRB,PB1);

	/* switch motor into clockwise */
	SET_BIT(PORTB,PB1);
	CLEAR_BIT(PORTB,PB0);

	/* ADC config ->
	 * - choose channel 0
	 * - choose AREF in micro-controller
	 * - choose polling not interrupt because it takes only 3 cycle
	 * - F_CPU / 8 = 1MHZ / 8 = 125KHZ (50 : 200 KHZ)
	 */
	ADC_configType ADC_config = {ADC0,AREF,Polling,F_CPU_8_};

	/* PWM config ->
	 * - choose PWM in Timer0
	 * - choose clear on compare match mode
	 * - choose F_CPU / 8
	 */
	PWM_configType PWM_config = {TIMER_0,CLEAR_OC0,F_CPU_8};

	/* Interrupt config ->
	 * - choose INT1
	 * - interrupt happend when rising edge happend
	 */
	INTERRUPT_configType INTERRUPT_config = {INTERRUPT_1,RISING_EDGE};

	/* pass config-structure to initial function of every module */
	ADC_init(&ADC_config);
	PWM_init(&PWM_config);
	INTERRUPT_init(&INTERRUPT_config);
	/* give interrupt module the cfunction which will happen when rising edge happen */
	INTERRUPT_1_callBack(Reverse_Direction);

	/* initiate lcd */
	LCD_init();
	/* Enable global interrupt >> sei(); */
	SREG |= (1<<7);

	LCD_displayString("ADC Value = ");

	while(1)
	{
		/* read potentiometer value form cahnnel 0 */
		g_adcResult = ADC_readChannel(&ADC_config);
		/* value of OCR0 = (adcValue * 256) / 1024 = adcValue / 4 */
		g_OCR0 = g_adcResult / 4;
		/* change duty cycle according to potentiometer value */
		PWM_changeDuty(&PWM_config,g_OCR0);
		/* display adcVaue on chosen place */
		LCD_goToRowColumn(0,12);
		/* these condition solve show 4 digits on lcd problem */

		if(g_adcResult > 1000)
		{
			LCD_intgerToString(g_adcResult);
		}
		else if(g_adcResult > 100 && g_adcResult < 1000)
		{
			LCD_displayString(" ");
			LCD_intgerToString(g_adcResult);
		}
		else if(g_adcResult > 10 && g_adcResult < 100)
		{
			LCD_displayString("  ");
			LCD_intgerToString(g_adcResult);
		}
		else if(g_adcResult < 10)
		{
			LCD_displayString("   ");
			LCD_intgerToString(g_adcResult);
		}

	}
}
