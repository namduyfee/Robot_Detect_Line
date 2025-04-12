
#include "main.h"
#include "FreeRTOS.h"
#include "task.h"

uint32_t temp =  10; 

void vTaskBlinkLED(void *pvParameters)
{
    (void)pvParameters;
    vTaskDelay(pdMS_TO_TICKS(3000)); // Delay 100 ms
    while (1)
    {
        temp =TIM2->CNT; 

        GPIOC->ODR ^= (1 << 13); // Toggle LED on PC13
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


