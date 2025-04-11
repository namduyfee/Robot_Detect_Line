
#include "handler.h"

void HardFault_Handler(void) 

{

    while(1) {
        toggle_led(); 
    }
}


