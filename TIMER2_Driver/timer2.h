/*
 * timer0.h
 *
 *  Created on: ??þ/??þ/????
 *      Author: Ahmed
 */

#ifndef TIMER2_H_
#define TIMER2_H_

#include "micro_config.h"
#include "std_types.h"
#include "common_macros.h"

/*******************************************************************************
 *                        External Variables                                   *
 *******************************************************************************/

extern uint8 g_initialCounter;
extern uint8 g_CTC_OCR2;

/*******************************************************************************
 *                         Types Declaration                                   *
 *******************************************************************************/

typedef enum
{
	OVERFLOW,CTC=2
}Timer2_Mode;

typedef enum
{
	NORMAL_OC2_DISCONNECTED,TOGGLE_OC2,CLEAR_OC2,SET_OC2
}Timer2_CTC_Mode;

typedef enum
{
	NO_CLOCK,F_CPU_CLOCK,F_CPU_8,F_CPU_64,F_CPU_256,F_CPU_1024,EXTERNAL_CLOCK_FALLING,EXTERNAL_CLOCK_RISING
}Timer2_Clock;

typedef enum
{
	NO_INTERRUPT,OVERFLOW_INTERRUPT, CTC_INTERRUPT
}Timer2_Interrupt_Mode;

typedef struct
{
	Timer2_Mode           Mode;
	Timer2_CTC_Mode       CTC_Mode;
	Timer2_Clock          Clcok;
	Timer2_Interrupt_Mode Enable_Interrupt;
	uint8                 CTC_Value;
}Timer2_configType;

/*******************************************************************************
 *                      Functions Prototypes                                   *
 *******************************************************************************/

void TIMER2_init(Timer2_configType * config_Ptr,uint8 a_initialCounter);

void TIMER2_setCallBack(void (*a_ptr)(void));

#endif /* TIMER2_H_ */
