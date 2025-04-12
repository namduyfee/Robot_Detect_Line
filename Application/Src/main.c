
#include "main.h"
#include "FreeRTOS.h"
#include "task.h"



void vTaskBlinkLED(void *pvParameters)
{
    (void)pvParameters;

    while (1)
    {
        servo1(20); 
        servo2(20);
        GPIOC->ODR ^= (1 << 13); // Toggle LED on PC13
        vTaskDelay(pdMS_TO_TICKS(1000)); // Delay 100 ms
        servo1(180); 
        servo2(180);
        vTaskDelay(pdMS_TO_TICKS(1000)); // Delay 100 ms
    }
}

void main(void)
{

    config_STM32F1();
    
    xTaskCreate(vTaskBlinkLED, "LED_Blink", 128, NULL, 1, NULL);
    vTaskStartScheduler();
    while(1); 

}


