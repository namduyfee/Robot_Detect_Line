
#include "GPIO_Driver.h"

void config_GPIOA(void)
{
	RCC->APB2ENR |= RCC_APB2ENR_IOPAEN;
	GPIOA->CRL &= 0xFFFF000F; 
}

void config_GPIOC(void) 
{
	RCC->APB2ENR |= RCC_APB2ENR_IOPCEN; 

	GPIOC->CRH = 0; 
	GPIOC->CRH |= (0x3<<20); 

}

void config_GPIOB(void)
{
	RCC->APB2ENR |= RCC_APB2ENR_IOPBEN;
	// CRH = 0
	GPIOB->CRH &= 0; 
	// PB8, PB9 output alternate open drain 
	GPIOB->CRH |= 0xFF;

}

void config_AFIO(void) 
{
	RCC->APB2ENR |= RCC_APB2ENR_AFIOEN;
	// I2C remap 
	AFIO->MAPR |= 1<<1; 
}

