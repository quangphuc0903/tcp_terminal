#ifndef __USART_H
#define __USART_H


#include "stm32f10x_usart.h"            // Keil::Device:StdPeriph Drivers:USART
#include "stm32f10x.h"                  // Device header
#include "delay.h"
#include "string.h"
#include "stdio.h"
#include "stm32f10x_rcc.h"              // Keil::Device:StdPeriph Drivers:RCC
#include "stm32f10x_gpio.h"             // Keil::Device:StdPeriph Drivers:GPIO
#include "stdlib.h"

#define MAX_FIELD       20
void USART_Config(USART_TypeDef* USARTx,uint32_t baud);
void USART_SendString_(USART_TypeDef* USARTx, char *s);
void USART1_IRQHandler(void);
void USART_PutChar(USART_TypeDef* USARTx,char c);
char* USART_get_string(USART_TypeDef* USARTx);
void USART1_IRQHandler(void);
void process_message_master(void);
int8_t _sms_process(char * msg, uint8_t len);
void action(void);
void return_status1(void);
void return_status2(void);
void U2_return_status1(void);
void U2_return_status2(void);
#endif

