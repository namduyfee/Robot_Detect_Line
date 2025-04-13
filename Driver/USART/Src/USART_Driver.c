
#include "USART_Driver.h"


volatile int uartPositionHeadU2 = -1; 
volatile int uartPositionHeadU3 = -1;


volatile uint8_t rxBufferU2[LENGTH_BUFFER_UART2]; 
volatile uint8_t rxBufferU3[LENGTH_BUFFER_UART3]; 

volatile uint8_t rxDataU1; 

void config_UART1(void) {
	
	RCC->APB2ENR |= RCC_APB2ENR_USART1EN; 
//	USART1->BRR = 0x1D4C; 				// 9600
	USART1->BRR = 0x271; 				// 115200

	USART1->CR1 |= (USART_CR1_RE | USART_CR1_RXNEIE | USART_CR1_UE); 
	


}

void config_UART2 (void) {
	RCC->APB1ENR |= RCC_APB1ENR_USART2EN; 
	
	USART2->CR3 |= USART_CR3_DMAR; 
	USART2->CR3 |= USART_CR3_DMAT;

//	USART2->BRR = 0xEA6;					// 9600
	USART2->BRR = 0x138; 				    // 115200

	USART2->CR1 |= (USART_CR1_RE | USART_CR1_TE | USART_CR1_UE); 
	
}

void config_UART3(void) {

	RCC->APB1ENR |= RCC_APB1ENR_USART3EN;

	USART3->CR3 |= USART_CR3_DMAR; 
	USART3->CR3 |= USART_CR3_DMAT;

//	USART3->BRR = 0xEA6;				// baudrate 9600
	USART3->BRR = 0x138; 				// 115200	

	USART3->CR1 |= (USART_CR1_RE | USART_CR1_TE | USART_CR1_UE);
}


