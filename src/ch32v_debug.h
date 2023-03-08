#ifndef __DEBUG_H
#define __DEBUG_H

#include <ch32v00x.h>
#include <stdio.h>

#define DEBUG_UART1 1

#ifndef DEBUG
#define DEBUG DEBUG_UART1
#endif

void Delay_Init(void);
void Delay_Us(uint32_t n);
void Delay_Ms(uint32_t n);
void USART_Printf_Init(uint32_t baudrate);

#endif

