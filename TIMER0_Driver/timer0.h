/*
 * timer0.h
 *
 *  Created on: ??þ/??þ/????
 *      Author: Ahmed
 */

#ifndef TIMER0_H_
#define TIMER0_H_

#include "micro_config.h"
#include "std_types.h"
#include "common_macros.h"

/*******************************************************************************
 *                        External Variables                                   *
 *******************************************************************************/

extern uint8 g_initialCounter;
extern uint8 g_CTC_OCR0;

/*******************************************************************************
 *                         Types Declaration                                   *
 *******************************************************************************/

typedef enum
{
	OVERFLOW,CTC=2
}Timer0_Mode;

typedef enum
{
	NORMAL_OC0_DISCONNECTED,TOGGLE_OC0,CLEAR_OC0,SET_OC0
}Timer0_CTC_Mode;

typedef enum
{
	NO_CLOCK,F_CPU_CLOCK,F_CPU_8,F_CPU_64,F_CPU_256,F_CPU_1024,EXTERNAL_CLOCK_FALLING,EXTERNAL_CLOCK_RISING
}Timer0_Clock;

typedef enum
{
	NO_INTERRUPT,OVERFLOW_INTERRUPT, CTC_INTERRUPT
}Timer0_Interrupt_Mode;

typedef struct
{
	Timer0_Mode           Mode;
	Timer0_CTC_Mode       CTC_Mode;
	Timer0_Clock          Clcok;
	Timer0_Interrupt_Mode Enable_Interrupt;
	uint8                 CTC_Value;
}Timer0_configType;

/*******************************************************************************
 *                      Functions Prototypes                                   *
 *******************************************************************************/

void TIMER0_init(Timer0_configType * config_Ptr,uint8 a_initialCounter);

void TIMER0_setCallBack(void (*a_ptr)(void));

#endif /* TIMER0_H_ */
