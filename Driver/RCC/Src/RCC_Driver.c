
#include "RCC_Driver.h"


//#define SYSCLK_FREQ_HSE    HSE_VALUE 
// #define SYSCLK_FREQ_24MHz  24000000 
// #define SYSCLK_FREQ_36MHz  36000000 
// #define SYSCLK_FREQ_48MHz  48000000 
// #define SYSCLK_FREQ_56MHz  56000000 
#define SYSCLK_FREQ_72MHz  72000000


#ifdef SYSCLK_FREQ_HSE
  #define SYSCLK SYSCLK_FREQ_HSE
#elif defined(SYSCLK_FREQ_24MHz)
  #define SYSCLK SYSCLK_FREQ_24MHz
#elif defined(SYSCLK_FREQ_36MHz)
  #define SYSCLK SYSCLK_FREQ_36MHz  
#elif defined(SYSCLK_FREQ_48MHz)
  #define SYSCLK SYSCLK_FREQ_48MHz
#elif defined(SYSCLK_FREQ_56MHz)
  #define SYSCLK SYSCLK_FREQ_56MHz
#elif defined(SYSCLK_FREQ_72MHz)
  #define SYSCLK SYSCLK_FREQ_72MHz
#endif


static void set_sys_clock(void);
static void set_sys_clock_to_HSE(void); 
static void calculate_clock(void); 


static void set_sys_clock_to_24(void); 
static void set_sys_clock_to_36(void); 
static void set_sys_clock_to_48(void); 
static void set_sys_clock_to_56(void); 
static void set_sys_clock_to_72(void); 

uint32_t SystemCoreClock;
uint32_t clockOfHCLK, clockOfPCLK1, clockOfPCLK2; 

void config_RCC(void)
{

    /* set HSI ON bit */
    RCC->CR |= (uint32_t)0x00000001;

    /* Reset SW, HPRE, PPRE1, PPRE2, ADCPRE and MCO bits */
    RCC->CFGR &= (uint32_t)0xF8FF0000;

    /* Reset HSEON, CSSON and PLLON bits */
    RCC->CR &= (uint32_t)0xFEF6FFFF;

    /* Reset HSEBYP bit */
    RCC->CR &= (uint32_t)0xFFFBFFFF;  

    /* Reset PLLSRC, PLLXTPRE, PLLMUL and USBPRE/OTGFSPRE bits */
    RCC->CFGR &= (uint32_t)0xFF80FFFF;   

    /* Disable all interrupts and clear pending bits  */
    RCC->CIR = 0x009F0000;

    set_sys_clock(); 

    calculate_clock(); 

}

static void calculate_clock(void) 
{
  uint32_t AHB_Div =  ( ((RCC->CFGR)>>4) & (uint32_t)(0x0F) );
  uint32_t APB1_Div = ( ((RCC->CFGR)>>8) & (uint32_t)(0x07) );
  uint32_t APB2_Div = ( ((RCC->CFGR)>>11) & (uint32_t)(0x07) );

  if(AHB_Div < 8 ) 
    clockOfHCLK = SYSCLK; 
  else {
    if(AHB_Div < 12)
      clockOfHCLK = SYSCLK / (pow(2, AHB_Div - 7)); 
    else 
     clockOfHCLK = SYSCLK / (pow(2, AHB_Div - 7 + 1));
  }

  if(APB1_Div < 4)
    clockOfPCLK1 = clockOfHCLK; 
  else {
    clockOfPCLK1 = clockOfHCLK / (pow(2, APB1_Div - 3)); 
  }

  if(APB2_Div < 4)
    clockOfPCLK2 = clockOfHCLK; 
  else {
    clockOfPCLK2 = clockOfHCLK / (pow(2, APB2_Div - 3)); 
  }
  SystemCoreClock = clockOfHCLK; 
}


static void set_sys_clock(void) 
{

    #ifdef SYSCLK_FREQ_HSE
      set_sys_clock_to_HSE();
    #elif defined SYSCLK_FREQ_24MHz
      set_sys_clock_to_24();
    #elif defined SYSCLK_FREQ_36MHz
      set_sys_clock_to_36();
    #elif defined SYSCLK_FREQ_48MHz
      set_sys_clock_to_48();
    #elif defined SYSCLK_FREQ_56MHz
      set_sys_clock_to_56();  
    #elif defined SYSCLK_FREQ_72MHz
      set_sys_clock_to_72();
  #endif    

}

#ifdef SYSCLK_FREQ_HSE
static void set_sys_clock_to_HSE(void) 
{
  __IO uint32_t StartUpCounter = 0, HSEStatus = 0;
  
  /* SYSCLK, HCLK, PCLK2 and PCLK1 configuration ---------------------------*/    
  /* Enable HSE */    
  RCC->CR |= ((uint32_t)RCC_CR_HSEON);

  /* Wait till HSE is ready and if Time out is reached exit */
  do {
    HSEStatus = RCC->CR & RCC_CR_HSERDY;
    StartUpCounter++;  
  } while((HSEStatus == 0) && (StartUpCounter != HSE_STARTUP_TIMEOUT));  

  if ((RCC->CR & RCC_CR_HSERDY) != RESET) 
    HSEStatus = (uint32_t)0x01;
  else 
    HSEStatus = (uint32_t)0x00;


  if (HSEStatus == (uint32_t)0x01) {
    /* Enable Prefetch Buffer */
    FLASH->ACR |= FLASH_ACR_PRFTBE;
    /* Flash 0 wait state */
    FLASH->ACR &= (uint32_t)((uint32_t)~FLASH_ACR_LATENCY);   
    FLASH->ACR |= (uint32_t)FLASH_ACR_LATENCY_0;

    /* HCLK = SYSCLK */
    RCC->CFGR |= (uint32_t)RCC_CFGR_HPRE_DIV1;
      
    /* PCLK2 = HCLK */
    RCC->CFGR |= (uint32_t)RCC_CFGR_PPRE2_DIV1;
    
    /* PCLK1 = HCLK */
    RCC->CFGR |= (uint32_t)RCC_CFGR_PPRE1_DIV1;
    
    /* Select HSE as system clock source */
    RCC->CFGR &= (uint32_t)((uint32_t)~(RCC_CFGR_SW));
    RCC->CFGR |= (uint32_t)RCC_CFGR_SW_HSE;    

    /* Wait till HSE is used as system clock source */
    while ((RCC->CFGR & (uint32_t)RCC_CFGR_SWS) != (uint32_t)0x04) {
    }    
  }

}

#elif SYSCLK_FREQ_24MHz
static void set_sys_clock_to_24(void)
{

}
#elif SYSCLK_FREQ_36MHz
static void set_sys_clock_to_36(void)
{

}

#elif SYSCLK_FREQ_48MHz
static void set_sys_clock_to_48(void)
{

}
#elif SYSCLK_FREQ_56MHz
static void set_sys_clock_to_56(void)
{

}

#elif SYSCLK_FREQ_72MHz
static void set_sys_clock_to_72(void)
{
  __IO uint32_t StartUpCounter = 0, HSEStatus = 0;
  
  /* SYSCLK, HCLK, PCLK2 and PCLK1 configuration ---------------------------*/    
  /* Enable HSE */    
  RCC->CR |= ((uint32_t)RCC_CR_HSEON);
 
  /* Wait till HSE is ready and if Time out is reached exit */
  do
  {
    HSEStatus = RCC->CR & RCC_CR_HSERDY;
    StartUpCounter++;  
  } while((HSEStatus == 0) && (StartUpCounter != HSE_STARTUP_TIMEOUT));

  if ((RCC->CR & RCC_CR_HSERDY) != RESET)
  {
    HSEStatus = (uint32_t)0x01;
  }
  else
  {
    HSEStatus = (uint32_t)0x00;
  }  

  if (HSEStatus == (uint32_t)0x01)
  {
    /* Enable Prefetch Buffer */
    FLASH->ACR |= FLASH_ACR_PRFTBE;

    /* Flash 2 wait state */
    FLASH->ACR &= (uint32_t)((uint32_t)~FLASH_ACR_LATENCY);
    FLASH->ACR |= (uint32_t)FLASH_ACR_LATENCY_2;    

 
    /* HCLK = SYSCLK */
    RCC->CFGR |= (uint32_t)RCC_CFGR_HPRE_DIV1;
    /* PCLK2 = HCLK */
    RCC->CFGR |= (uint32_t)RCC_CFGR_PPRE2_DIV1;
    /* PCLK1 = HCLK div 2 */
    RCC->CFGR |= (uint32_t)RCC_CFGR_PPRE1_DIV2;
    /*  PLL configuration: PLLCLK = HSE * 9 = 72 MHz */
    RCC->CFGR &= (uint32_t)((uint32_t)~(RCC_CFGR_PLLSRC | RCC_CFGR_PLLXTPRE |
        RCC_CFGR_PLLMULL));
    RCC->CFGR |= (uint32_t)(RCC_CFGR_PLLSRC_HSE | RCC_CFGR_PLLMULL9);    
    /* Enable PLL */
    RCC->CR |= RCC_CR_PLLON;

    /* Wait till PLL is ready */
    while((RCC->CR & RCC_CR_PLLRDY) == 0)
    {
    }
    
    /* Select PLL as system clock source */
    RCC->CFGR &= (uint32_t)((uint32_t)~(RCC_CFGR_SW));
    RCC->CFGR |= (uint32_t)RCC_CFGR_SW_PLL;    

    /* Wait till PLL is used as system clock source */
    while ((RCC->CFGR & (uint32_t)RCC_CFGR_SWS) != (uint32_t)0x08)
    {
    }
  }
  else
  { /* If HSE fails to start-up, the application will have wrong clock 
         configuration. User can add here some code to deal with this error */
  }
}  
#endif



