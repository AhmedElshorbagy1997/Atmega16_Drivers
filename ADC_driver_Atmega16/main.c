/*
 * main.c
 *
 *  Created on: 8/1/2020
 *      Author: Ahmed Mohamed Elshorbagy
 */


#include "adc.h"
#include "lcd.h"

int main(void)
{
	/* initialize LCD driver */
	LCD_init();

	/* Create configuration structure for ADC driver */
	ADC_configType ADC_config = {ADC0,AREF,Polling,F_CPU_8};

	/* initialize ADC driver */
	ADC_init(&ADC_config);

	/* clear LCD at the beginning */
	LCD_clearScreen();

	/* display this string "ADC0 Value = " only once at LCD */
	LCD_goToRowColumn(0,0);
	LCD_displayString("ADC0 Value = ");

	/* display this string "ADC3 Value = " only once at LCD */
	LCD_goToRowColumn(1,0);
	LCD_displayString("ADC3 Value = ");

    while(1)
    {
    	/* display the number every time at this position */
		LCD_goToRowColumn(0,12);

		/* choose ADC0 to where the first potentiometer is connect */
		ADC_config.channel = ADC0;

		/* read the selected channel */
		g_adcResult = ADC_readChannel(&ADC_config);

		/* display the ADC0 value on LCD screen */
		LCD_intgerToString(g_adcResult);

		/* display the number every time at this position */
		LCD_goToRowColumn(1,12);

		/* choose ADC0 to where the second potentiometer is connect */
		ADC_config.channel = ADC3;

		/* read the selected channel */
		g_adcResult = ADC_readChannel(&ADC_config);

		/* display the ADC0 value on LCD screen */
		LCD_intgerToString(g_adcResult);
    }
}
