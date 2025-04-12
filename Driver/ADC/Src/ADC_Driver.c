
#include "ADC_Driver.h"

#define CLOCK_MAX_ADC 14000000

static void prescaler_clock_ADC(void); 
static void error_ADC(void); 

uint32_t clockADC; 
uint16_t valueADC1[16]; 

void config_ADC1(void) 
{
    prescaler_clock_ADC(); 
    RCC->APB2ENR |= RCC_APB2ENR_ADC1EN;

	ADC1->CR1   |= (ADC_CR1_SCAN); 

	ADC1->CR2   |= (ADC_CR2_CONT | ADC_CR2_EXTSEL | ADC_CR2_EXTTRIG | ADC_CR2_DMA); 
	// 3 convert
	ADC1->SQR1  |= (ADC_SQR1_L_1); 
	// channel 2 is the fist convert, channel 3 is second convert, channel 4 is third convert
	ADC1->SQR3  |= (ADC_SQR3_SQ1_1  | (ADC_SQR3_SQ2_0 | ADC_SQR3_SQ2_1) |  ADC_SQR3_SQ3_2); 
	// sample time 
	ADC1->SMPR2 |= (ADC_SMPR2_SMP2 | ADC_SMPR2_SMP3 | ADC_SMPR2_SMP4);  

	ADC1->CR2   |= (ADC_CR2_ADON); 
	// enable regular  by bit swstart 
	ADC1->SR = 0; 
	ADC1->CR2   |= (ADC_CR2_SWSTART); 
}

static void prescaler_clock_ADC(void) 
{
    uint32_t ADCPRE = 0;
    uint8_t completed = 0; 

    for(int i = 0; i < 4; i++) {
        ADCPRE = i;
        clockADC = clockOfPCLK2 / (2*(i+1)); 
        if(clockADC <= CLOCK_MAX_ADC) {
            completed = 1; 
            break;
        }
    }
    if(completed == 0)
        error_ADC(); 
    else {
        RCC->CFGR |= (uint32_t)(ADCPRE << 14); 
    }
}

static void error_ADC(void)
{
    while(1) {

    }

}
