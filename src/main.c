#include "ch32v00x.h"
#include "ch32v_debug.h"
#include <stdio.h>

int static_display = 0;
int LED_value = 0;

void initialize() {
	NVIC_InitTypeDef NVIC_InitStructure;
	USART_InitTypeDef USART_InitStructure;
	GPIO_InitTypeDef GPIO_InitStructure;

	RCC_APB2PeriphClockCmd(
		RCC_APB2Periph_GPIOC | RCC_APB2Periph_GPIOD | RCC_APB2Periph_USART1,
		ENABLE
	);

	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_5;
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF_PP;
	GPIO_Init(GPIOD, &GPIO_InitStructure);

	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_1;
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_Out_PP;
	GPIO_Init(GPIOC, &GPIO_InitStructure);

	USART_InitStructure.USART_BaudRate = 9600;
	USART_InitStructure.USART_WordLength = USART_WordLength_8b;
	USART_InitStructure.USART_StopBits = USART_StopBits_1;
	USART_InitStructure.USART_Parity = USART_Parity_No;
	USART_InitStructure.USART_HardwareFlowControl = USART_HardwareFlowControl_None;
	USART_InitStructure.USART_Mode = USART_Mode_Tx | USART_Mode_Rx;

	USART_Init(USART1, &USART_InitStructure);
	USART_ITConfig(USART1, USART_IT_RXNE, ENABLE);

	NVIC_PriorityGroupConfig(NVIC_PriorityGroup_2);

	NVIC_InitStructure.NVIC_IRQChannel = USART1_IRQn;
	NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = 2;
	NVIC_InitStructure.NVIC_IRQChannelSubPriority = 2;
	NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;
	NVIC_Init(&NVIC_InitStructure);

	USART_Cmd(USART1, ENABLE);
}

void loop() {
	GPIO_WriteBit(GPIOC, GPIO_Pin_1, !LED_value);

	if (!static_display)
		LED_value = !LED_value;

	Delay_Ms(100);
}

void main() {
	Delay_Init();
	initialize();
	printf("System is ready now. SystemClock: %d\r\n", SystemCoreClock);

	while (1)
		loop();
}

__attribute__((interrupt("WCH-Interrupt-fast")))
void USART1_IRQHandler() {
	switch (USART_ReceiveData(USART1)) {
	case '0':
		static_display = 1;
		LED_value = 0;
		break;
	case '1':
		static_display = 1;
		LED_value = 1;
		break;
	default:
		static_display = 0;
	}
}

