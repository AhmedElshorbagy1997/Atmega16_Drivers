/*
 * adc.c
 *
 *  Created on: ??þ/??þ/????
 *      Author: Ahmed
 */


#include "adc.h"

volatile uint16 g_adcResult = 0;

ISR(ADC_vect)
{
	g_adcResult = ADC;
}

void ADC_init(const ADC_configType * config_Ptr)
{
	ADMUX = ((config_Ptr->reference)<<5);
	SET_BIT(ADCSRA,ADEN);
	SET_BIT(ADCSRA,ADEN);
	ADCSRA |= ((config_Ptr->mode)<<ADIE);
	ADCSRA = (ADCSRA & 0xF8) | ((config_Ptr->Division) & 0x07);
}

uint16 ADC_readChannel(const ADC_configType * config_Ptr)
{
	ADMUX = (ADMUX & 0xE0) | ((config_Ptr->channel) & 0x07);
	SET_BIT(ADCSRA,ADSC);
	if((config_Ptr->mode) == Polling)
	{
		while(BIT_IS_CLEAR(ADCSRA,ADIF));
		SET_BIT(ADCSRA,ADIF);
	}
	return ADC;
}
