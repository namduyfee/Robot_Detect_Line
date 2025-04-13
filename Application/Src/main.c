
#include "main.h"
#include "vTask1.h"
#include "vTask2.h"
#include "vTask3.h"
#include "vTask4.h"

void main(void)
{

    config_STM32F1();
    
    xTaskCreate(vTask1, "LED_Blink", 128, NULL, 1, NULL);
    xTaskCreate(vTask2, "Read_TIMER_Capture", 128, NULL, 1, NULL);
    xTaskCreate(vTask3, "Control_Motor", 128, NULL, 1, NULL);
    xTaskCreate(vTask4, "USART", 128, NULL, 1, NULL);


    vTaskStartScheduler();
    while(1); 

}


