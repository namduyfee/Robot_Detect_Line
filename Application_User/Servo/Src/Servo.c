

#include "Servo.h"


/*
 * not must calculate ratio afterthat * angle 
   ex: TIM3->CCR1 = 250 + 6 (this is ratio) * angle;
   that cause errors ex: angle 180 -> TIM3->CCR1 = 250 + 6 * 180 -> result > 2.5ms
   errors will be increased with ticksOfOneMs, ticksOfOneMs more bigger then errors more bigger

   * So we must use (ticksOfOneMs / 2 ) + (ticksOfOneMs * 2 * angle) / 180;
   that avoid errors from calculation, and avoid rounding

   * because pwm mode 1, CNT < CCRx is active, so CCRx not - 1 
     ex: CCRx = 50 -> CNT < 50 is active -> CNT max = 49 <=> 50 pulse so not - 1 in CCRx 

 */
void servo1(int angle) 
{
	// 0 <= angle <= 180 
	uint16_t ticksOfOneMs = ((TIM3->ARR + 1) / 20); 	// (TIM3->ARR + 1) because has final pulse from ARR -> 0 

	// servo 0.5ms -> 2.5 ms
	TIM3->CCR1 = ( (ticksOfOneMs / 2 ) + (ticksOfOneMs * 2 * angle) / 180 );
	/* 
	// servo 1ms -> 2ms 
	TIM2->CCR2 = ticksOfOneMs + (ticksOfOneMs * 1 * angle) / 180;
	*/
	TIM3->CCER |= 1; 
	
}

void servo2(int angle) 
{
    uint16_t ticksOfOneMs = ((TIM3->ARR + 1) / 20);

	// 0 <= angle <= 180 
	// servo 0.5ms -> 2.5 ms
	TIM3->CCR2 = ( (ticksOfOneMs / 2 ) + (ticksOfOneMs * 2 * angle) / 180 ); 
	/* 
	// servo 1ms -> 2ms 
	TIM3->CCR2 = ticksOfOneMs + (ticksOfOneMs * 1 * angle) / 180;
	*/
	TIM3->CCER |= 1<<4; 
}

