

#include "DMA_Driver.h"

void config_DMA1(void) 
{
	
	RCC->AHBENR  |= RCC_AHBENR_DMA1EN;
	
	// channel 1 = ADC1
	DMA1_Channel1->CCR |= (DMA_CCR1_CIRC | DMA_CCR1_MINC | DMA_CCR1_PSIZE_0 | DMA_CCR1_MSIZE_0 | DMA_CCR1_PL_1);

	// channel 2 : tx_usart 3
	DMA1_Channel2->CCR |= (DMA_CCR2_DIR | DMA_CCR2_CIRC | DMA_CCR2_MINC | DMA_CCR2_PL_0);

	// channel 3 : rx_usart3
	DMA1_Channel3->CCR |= (DMA_CCR3_CIRC | DMA_CCR3_MINC | DMA_CCR3_PL_0);

	// channel 4 : tx_usart 1
	DMA1_Channel4->CCR |= (DMA_CCR4_DIR | DMA_CCR4_CIRC | DMA_CCR4_MINC | DMA_CCR4_PL_0);

	// channel 5 : rx_usart 1
	DMA1_Channel5->CCR |= (DMA_CCR5_CIRC | DMA_CCR5_MINC | DMA_CCR5_PL_0);

	// channel 6 : rx_usart 2
	DMA1_Channel6->CCR |= (DMA_CCR6_CIRC | DMA_CCR6_MINC | DMA_CCR6_PL_0);

	// channel 7 : tx_usart 2	
	DMA1_Channel7->CCR |= (DMA_CCR7_DIR | DMA_CCR7_CIRC | DMA_CCR7_MINC | DMA_CCR7_PL_0);


}


void initDMAChannel(DMA_Channel_TypeDef* DMA_Channel, volatile void* address_memory, 
                     volatile uint32_t* address_periph, uint16_t size) 
{
	DMA_Channel->CNDTR = size; 
	DMA_Channel->CMAR = (uint32_t)address_memory; 
	DMA_Channel->CPAR = (uint32_t)address_periph; 
	// enable DMA channelx
	DMA_CHANNEL_EN(DMA_Channel); 
}

