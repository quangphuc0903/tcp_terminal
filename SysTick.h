#ifndef _SysTick_H
#define _SysTick_H

#include "system.h"





void SysTick_Init(void);
void delay_ms(__IO uint32_t nTime);
void delay_us(uint32_t nus);
void TimingDelay_Crement(void);
uint64_t millis(void);

#endif
