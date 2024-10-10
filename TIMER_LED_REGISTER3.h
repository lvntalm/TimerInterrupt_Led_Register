#ifndef _TIMER_LED_REGISTER__
#define _TIMER_LED_REGISTER__

#include "stm32f407xx.h"

void GPIO_Clock_Init();
void TIM2_Clock_Init();
void GPIO_Init();
void TIM2_Init();
void TIM2_ChannelSettings();
void TIM2_CounterStart();
void NVIC_Enable();
void NVIC_Priority();
void TIM2_IRQHandler(void);

#endif
