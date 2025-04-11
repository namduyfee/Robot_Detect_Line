
#include "config.h"

void config_STM32F1(void) 
{
    config_RCC(); 
    config_TIM4(); 
    config_GPIOA(); 
    config_GPIOC(); 
    config_DMA1(); 
    initDMAChannel(DMA1_Channel1, (uint16_t*)valueADC1, (uint32_t*)(&(ADC1->DR)), 3); 
    config_ADC1(); 
    
}

