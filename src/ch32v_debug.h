#ifndef __DEBUG_H
#define __DEBUG_H

#include <ch32v00x.h>
#include <stdio.h>

#define DEBUG_UART1 1

#ifndef DEBUG
#define DEBUG DEBUG_UART1
#endif

void USART_Printf_Init(uint32_t baudrate);

#endif

