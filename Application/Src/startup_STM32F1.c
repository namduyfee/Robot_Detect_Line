
#include <stdint.h> 
#include "startup_STM32F1.h"
#include "main.h"

typedef void (*ISR_Handler)(void);


ISR_Handler vectors[] __attribute__((section(".isr_vector"))) = {
    (ISR_Handler)STACK_START,                        // Initial Stack Pointer
    Reset_Handler,              // Reset
    NMI_Handler,                // NMI
    HardFault_Handler,          // Hard Fault
    MemManage_Handler,          // MemManage
    BusFault_Handler,           // BusFault
    UsageFault_Handler,         // UsageFault
    0, 0, 0, 0,                 // Reserved
    SVC_Handler,                // SVCall
    DebugMon_Handler,           // Debug monitor
    0,                          // Reserved
    PendSV_Handler,             // PendSV
    SysTick_Handler,            // SysTick
    WWDG_IRQHandler,            // Window Watchdog
    PVD_Handler,                // PVD through EXTI Line
    TAMPER_IRQHandler,          // Tamper
    RTC_IRQHandler,             // RTC
    FLASH_IRQHandler,           // Flash
    RCC_IRQHandler,             // RCC
    EXTI0_IRQHandler,           // EXTI Line 0
    EXTI1_IRQHandler,           // EXTI Line 1
    EXTI2_IRQHandler,           // EXTI Line 2
    EXTI3_IRQHandler,           // EXTI Line 3
    EXTI4_IRQHandler,           // EXTI Line 4
    DMA1_Channel1_IRQHandler,
    DMA1_Channel2_IRQHandler,
    DMA1_Channel3_IRQHandler,
    DMA1_Channel4_IRQHandler,
    DMA1_Channel5_IRQHandler,
    DMA1_Channel6_IRQHandler,
    DMA1_Channel7_IRQHandler,
    ADC1_2_IRQHandler,
    USB_HP_CAN1_TX_IRQHandler,
    USB_LP_CAN1_RX0_IRQHandler,
    CAN1_RX1_IRQHandler,
    CAN1_SCE_IRQHandler,
    EXTI9_5_IRQHandler,
    TIM1_BRK_IRQHandler,
    TIM1_UP_IRQHandler,
    TIM1_TRG_COM_IRQHandler,
    TIM1_CC_IRQHandler,
    TIM2_IRQHandler,
    TIM3_IRQHandler,
    TIM4_IRQHandler,
    I2C1_EV_IRQHandler,
    I2C1_ER_IRQHandler,
    I2C2_EV_IRQHandler,
    I2C2_ER_IRQHandler,
    SPI1_IRQHandler,
    SPI2_IRQHandler,
    USART1_IRQHandler,
    USART2_IRQHandler,
    USART3_IRQHandler,
    EXTI15_10_IRQHandler,
    RTC_Alarm_IRQHandler,
    USBWakeUp_IRQHandler
};

void Reset_Handler(void) {
    // copy .data section to RAM
    unsigned int size = (unsigned int)&_edata - (unsigned int)&_sdata; 
    unsigned char* pDst = (unsigned char*)&_sdata;           // SRAM
    unsigned char* pSrc = (unsigned char*) &_la_data;        // FLASH
    for(unsigned int i = 0; i < size; i++) {
        *pDst++ = *pSrc++; 
    }
    // init .bss section to zezo in RAM
    size = (unsigned int)&_ebss - (unsigned int)&_sbss; 
    pDst = (unsigned char*)&_sbss; 
    for(unsigned int i = 0; i < size; i++) {
        *pDst++ = 0; 
    }
    // call main() 
    main(); 

} 

void Default_Handler(void) 
{

    while(1) {
        toggle_led();
    }

}

