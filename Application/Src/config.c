
#include "config.h"

void config_STM32F1(void) 
{
    config_RCC(); 
    enable_clock_peripherals(); 

}

