
#ifndef __FUNC_FREERTOS__

#define __FUNC_FREERTOS__

#include "main.h"
#include "FreeRTOS.h"
#include "task.h"

extern uint32_t SystemCoreClock; 

void vApplicationMallocFailedHook(void); 
void vApplicationStackOverflowHook(TaskHandle_t xTask, char *pcTaskName);


#endif

