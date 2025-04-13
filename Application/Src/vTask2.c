
#include "main.h"

uint16_t temCNT; 

void vTask2(void *pvParameters)
{
    (void)pvParameters;
    while (1)
    {

        temCNT =TIM2->CNT; 
        vTaskDelay(pdMS_TO_TICKS(1));
    
    }
}

