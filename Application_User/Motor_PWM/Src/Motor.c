
#include "Motor.h"

void control_DC1(uint16_t speed)
{
    TIM1->CCR1 = speed; 
    TIM1->CCER |= 1; 
}

void control_DC2(uint16_t speed)
{
    TIM1->CCR2 = speed;
    TIM1->CCER |= 1<<4; 
}

void control_DC3(uint16_t speed)
{
    TIM1->CCR3 = speed;
    TIM1->CCER |= 1<<8; 

}

void control_DC4(uint16_t speed)
{
    TIM1->CCR4 = speed;
    TIM1->CCER |= 1<<12; 
}

