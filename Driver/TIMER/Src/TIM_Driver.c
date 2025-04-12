
#include "TIM_Driver.h"


// TIM1 control 4 motor 
void config_TIM1(void) 
{
    RCC->APB2ENR |= RCC_APB2ENR_TIM1EN; 

    TIM1->ARR = 1000-1; 
    TIM1->PSC = 36-1; 

    // center-aligned 
    TIM1->CR1 |= 1<<5; 
    TIM1->CR1 |= 1<<6; 
    // set bit MOE
    TIM1->BDTR |= 1<<15; 							

    // channel 1 PWM mode 1 
    TIM1->CCMR1 &= 0xFFF0; 
    TIM1->CCMR1 |= 0x60; 
    // channel 2 PWM mode 1 
    TIM1->CCMR1 &= 0xF0FF; 
    TIM1->CCMR1 |= 0x6000; 
    // channel 3 PWM mode 1 
    TIM1->CCMR2 &= 0xFFF0; 
    TIM1->CCMR2 |= 0x60; 
    // channel 4 PWM mode 1  
    TIM1->CCMR2 &= 0xF0FF;  
    TIM1->CCMR2 |= 0x6000; 

    TIM1->CCR1 = 500; 
    TIM1->CCR2 = 500;
    TIM1->CCR3 = 500;
    TIM1->CCR4 = 500;

    TIM1->CCER |= (1 | 1<<4 | 1<<8 | 1<<12); 

    // set bit UG 
    TIM1->EGR |= 1; 			
    // enable counter 
    TIM1->CR1 |= 1; 												
}

// timer 2 read color sensor
void config_TIM2(void)
{
    RCC->APB1ENR |= RCC_APB1ENR_TIM2EN;

    TIM2->ARR = 65535-1; 
    TIM2->PSC = 72-1; 

    //	// slave mode : reset 
    TIM2->SMCR |= 1<<2; 
    TIM2->SMCR |= 0x60; 

    // channel 2 input capture 
    // TI2 map IC2 

    TIM2->CCMR1 |= 1<<8; 
    //	// enable capture 
    TIM2->CCER |= 1<<4; 

    TIM2->EGR |= 1; 
    TIM2->CR1 |= 1; 
}
    
/* 
 * TIM3 control servo use channel 1 and channel 2
 * cycle 20 ms
 */
void config_TIM3(void) 
{
    RCC->APB1ENR |= RCC_APB1ENR_TIM3EN;   

    TIM3->ARR = 10000-1; 

    if( (clockOfHCLK / clockOfPCLK2) == 1) {
        TIM3->PSC = ( ((clockOfPCLK2 * 1) / ((TIM3->ARR) + 1)) / 50 ) - 1; 
    } 
    else {

        TIM3->PSC = ( ((clockOfPCLK2 * 2) / ((TIM3->ARR) + 1)) / 50 ) - 1;
    }

    TIM3->CCMR1 |= ( (TIM_CCMR1_OC1M_1 | TIM_CCMR1_OC1M_2) | (TIM_CCMR1_OC2M_1 | TIM_CCMR1_OC2M_2) ); 

    TIM3->EGR |= TIM_EGR_UG;  
    TIM3->CR1 |= TIM_CR1_CEN; 
}

void config_TIM4(void) 
{
    RCC->APB1ENR |= RCC_APB1ENR_TIM4EN;
    
    // config TIM4
    TIM4->ARR = 2000-1; 
    TIM4->PSC = 72-1; 
    TIM4->EGR |= 1; 
    TIM4->CR1 |= 1; 
}

// Hàm toggle LED
void toggle_led(void) 
{
    GPIOC->ODR ^= (1 << 13);
    delayUs(1000000); 

}
    
void delayUs(uint32_t us) 
{
    
    while(us) {
    // SysTick->VAL = 0; 
        TIM4->CNT = 0; 
        while(TIM4->CNT == 0); 
        us--; 
    }
}



