
#include "config.h"

void config_STM32F1(void) 
{
    config_RCC(); 
    config_AFIO(); 

    config_GPIOA(); 
    config_GPIOB(); 
    config_GPIOC(); 
    config_TIM4(); 
    config_TIM3(); 
    config_TIM2(); 
    config_TIM1(); 
    control_DC1(400); 
    control_DC2(500);
    control_DC3(600);
    control_DC4(700);

    config_DMA1(); 
    initDMAChannel(DMA1_Channel1, (uint16_t*)valueADC1, (uint32_t*)(&(ADC1->DR)), 3); 
    config_ADC1(); 
    
}

