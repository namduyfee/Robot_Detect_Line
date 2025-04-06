
#include "GPIO_Driver.h"


void config_GPIOC(void) 
{

	GPIOC->CRH = 0; 
	GPIOC->CRH |= (0x3<<20); 
	OFF_LED_SAMPLE_KALMAN; 


}

void config_GPIOB(void)
{
	// CRH = 0
	GPIOB->CRH &= 0; 
	// PB8, PB9 output alternate open drain 
	GPIOB->CRH |= 0xFF;

}

void config_AFIO(void) 
{
	// I2C remap 
	AFIO->MAPR |= 1<<1; 
}

