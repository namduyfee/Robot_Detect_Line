#include "vTask1.h"



void vTask1(void *pvParameters)
{
    (void)pvParameters;
    while (1)
    {
        vTaskDelay(pdMS_TO_TICKS(1));

    }
}

