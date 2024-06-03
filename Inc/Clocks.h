//
#ifndef _CLOCKS_H
#define _CLOCKS_H

#include <stdint.h>
#include <stdbool.h>

//
// global constants
//
#define CLOCK_FREQUENCY       64000000

#define CLOCKS_PER_SYSTICK    (CLOCK_FREQUENCY / 1000)

#define SYSTICKS_PER_LOOP     10

#define DELAY_US_MULTIPLIER   (CLOCK_FREQUENCY / 3500000)  // magic number

//
// system clock struct
//
typedef struct
{
  uint32_t SYSCLK_Frequency;        /*!< SYSCLK clock frequency */
  uint32_t HCLK_Frequency;          /*!< HCLK clock frequency */
  uint32_t PCLK1_Frequency;         /*!< PCLK1 clock frequency */
  uint32_t PCLK2_Frequency;         /*!< PCLK2 clock frequency */
  uint32_t ADCCLK_Frequency;
  uint32_t TIMER1_Frequency;
  uint32_t TIMER2_Frequency;
  uint32_t TIMER5_Frequency;
  uint32_t TIMER6_Frequency;
  
} RCU_ClocksTypeDef;

//
// clock timer type def
//
typedef struct
{
  uint32_t u32MaxCycleTime;
  uint32_t u32MinCycleTime;
  uint32_t u32OvrCycleTime;
  uint32_t u32CycleNumber;
  uint32_t u32OverrunCycleNmbr;
  uint16_t u16NmbrOfOverruns;
  bool bCycleOvrFlag;
  bool bCycleTimeFlag;
} loop_timers_st;

extern volatile uint32_t    systick_counter;

//
// exported functions
//
void ClearCycleTimeFlag(void);
void InitCycleClock(void);
//void Sleep(void);
uint32_t u32GetTick(void);
uint32_t u32GetSysTick(void);
void WaitForCycleTime(void);
void StartLoopOvrDetection(void);
void GetSystemClocks(void);
#endif

// eof Clocks.h
