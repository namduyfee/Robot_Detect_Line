
#include "vTask3.h"

uint16_t speedMotor1, speedMotor2, speedMotor3, speedMotor4; 

void vTask3(void *pvParameters)
{
    (void)pvParameters;
    speedMotor1 = 400; 
    speedMotor2 = 500; 
    speedMotor3 = 600; 
    speedMotor4 = 700; 

    while (1)
    {
        control_DC1(speedMotor1); 
        control_DC2(speedMotor2);
        control_DC3(speedMotor3);
        control_DC4(speedMotor4);
        vTaskDelay(pdMS_TO_TICKS(1));
        
    }
}

