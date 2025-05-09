
#include "GPIO_Driver.h"

void config_GPIOA(void)
{
	RCC->APB2ENR |= RCC_APB2ENR_IOPAEN;
	GPIOA->CRL = 0;
	GPIOA->CRH = 0;  

	GPIOA->CRL |= 0x08;        // PA0 input pull up/pull down
	GPIOA->ODR |= 1;           // PA0 input pull up

	GPIOA->CRL |= 0x08<<4;     // PA1 input pull up/pull down
	GPIOA->ODR |= 1<<1;        // PA1 input pull up	

	GPIOA->CRL |= 0x0B<<24; 		// PA6 alternate function push-pull
	GPIOA->CRL |= 0x0B<<28;			// PA7 alternate function push-pull

	// PA8, PA9, PA10, PA11 alternate function push-pull
	GPIOA->CRH |= 0x0B; 			
	GPIOA->CRH |= 0x0B<<4; 
	GPIOA->CRH |= 0x0B<<8;
	GPIOA->CRH |= 0x0B<<12;
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

	GPIOB->CRL = 0; 
	GPIOB->CRH = 0; 
	/* 

     * PB3 is pin JTAG, so want to use PB3 then must remap pin JTAG

	GPIOB->CRL |= 0x08<<12;     // PA3 input pull up/pull down
	GPIOB->ODR |= 1<<3;         // PA3 input pull up

	 */

	// PB8, PB9 output alternate open drain 
	GPIOB->CRH |= 0xFF;


}



