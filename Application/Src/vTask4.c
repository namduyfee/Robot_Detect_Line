
#include "vTask4.h"

void vTask4(void *pvParameters)
{
    (void)pvParameters;

    while (1)
    {
        CHECK_HEAD_UART(rxBufferU2, uartPositionHeadU2, LENGTH_BUFFER_UART2);
        CHECK_HEAD_UART(rxBufferU3, uartPositionHeadU3, LENGTH_BUFFER_UART3); 

        vTaskDelay(pdMS_TO_TICKS(1));
    }

}
