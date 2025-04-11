
#include "freeRTOS_hook.h"


void vApplicationMallocFailedHook(void)
{
    // Có thể dùng để log lỗi hoặc nháy LED báo lỗi
    while(1);
}

void vApplicationStackOverflowHook(TaskHandle_t xTask, char *pcTaskName)
{
    (void)xTask;
    (void)pcTaskName;

    // Xử lý khi task bị tràn stack, ví dụ: reset MCU, log lỗi, nháy LED
    while(1);
}

