
#include "handler.h"

void HardFault_Handler(void) 

{

    while(1) {
        toggle_led(); 
    }
}

void EXTI0_IRQHandler(void)
{
	if( EXTI->PR & (1<<0) ) {
        
        
		EXTI->PR = 1<<0; 
	}
}

void USART1_IRQHandler (void) {
	
	if(USART1->SR & (1<<5)) {
        rxDataU1 = USART1->DR; 
	}
	
}



