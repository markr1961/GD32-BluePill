
//
// Clocks.c
//
#include "ICF_Symbols.h"
#include "Clocks.h"
#include "Hardware.h"

//
volatile uint32_t  systick_counter;

static RCU_ClocksTypeDef   stSystemClocks = {0};
static uint32_t u32StartTime;
static uint32_t u32CycleTime;
volatile loop_timers_st stClocks;

static uint8_t    u8SysTicks; // counts 1mS systicks between overrun checks

//
// functions
//
void systick_config(void);
uint32_t u32GetTimerClock(uint32_t);
void GetSystemClocks(void);

/*************************************************************************
 *  FUNCTION NAME :
 *      delay_ms
 *
 *  FUNCTIONAL DESCRIPTION :
 *      delay_ the specified number of milliseconds
 *
 *  FORMAL INPUT PARAMETERS :
 *      ms - The number of milliseconds.
 *
 *      Note that this always ensures that the delay is from n to n+1
 *      milliseconds, synchronized to the master 1ms clock. When trying
 *      to do multiple 1ms delays, use 0 for all but the first call.
 ************************************************************************/
void delay_ms(clock_t ms)
{
  clock_t  t;

  t = clock();
  while(clock() - t < ms + 1) /* wait */
    ;
}

void systick_config(void)
{
    /* setup systick timer for 1000Hz interrupts */
    if (SysTick_Config(SystemCoreClock / 1000U)){
        /* capture error */
        while (1){
        }
    }
    /* configure the systick handler priority */
    NVIC_SetPriority(SysTick_IRQn, 0x00U);
}


// Checks the saved start time on the SysTick timer against the current time 
// and the cycle length to see if the previous cycle overran. If so, the overrun
// cycle number is recorded, the overrun counter is incremented.
//
static void CheckForTimerOverrun(void)
{
  STATIC uint32_t u32Temp;

  stClocks.bCycleOvrFlag = false;

  // Calculate how long the previous cycle took.  The SysTick timer counts down
  // from its max, so start time should always be a higher number.  If this is
  // not the case, we definitely have an overrun.
  u32Temp = u32GetTick(); // get current time first, in case it rolls over
  u32StartTime += CLOCKS_PER_SYSTICK * (uint32_t)(u8SysTicks);  // adjust for 1mS SysTick
  u32CycleTime = (u32StartTime - u32Temp) + stClocks.u32OvrCycleTime;

  if (u32CycleTime > CLOCKS_PER_SYSTICK * SYSTICKS_PER_LOOP)
  {
    stClocks.u16NmbrOfOverruns++;
    stClocks.u32OverrunCycleNmbr = stClocks.u32CycleNumber;
    ClearCycleTimeFlag();
  }

  if (u32CycleTime < stClocks.u32MinCycleTime)
  { // if we were faster than before, record it.
    stClocks.u32MinCycleTime = u32CycleTime;
  }
  if (u32CycleTime > stClocks.u32MaxCycleTime)
  { // if we were slower than before, record it.
    stClocks.u32MaxCycleTime = u32CycleTime;
  }
}

//
//
void ClearCycleTimeFlag(void)
{
  stClocks.bCycleTimeFlag = false;
  u32StartTime = u32GetTick();
  u8SysTicks = 0;
  // Increment the cycle number
  stClocks.u32CycleNumber++;

  stClocks.u32OvrCycleTime = 0;
}

//
//
void StartLoopOvrDetection(void)
{
  stClocks.bCycleOvrFlag = true;
}

//
//
//
void InitCycleClock(void)
{
  systick_counter = 0;

  // Should now be running at 120.0MHz. Calculate and save the 
  // system clock frequencies.
  GetSystemClocks();

  //Initialize the device variables
  stClocks.u32MaxCycleTime  = 0x00000000;
  stClocks.u32MinCycleTime  = 0xFFFFFFFF;
  stClocks.u16NmbrOfOverruns  = 0;
  stClocks.u32CycleNumber = 0;
  stClocks.bCycleTimeFlag = false;
  stClocks.bCycleOvrFlag  = false;

  //Initialize the local variables
  u32StartTime = 0x00000000;
  u32CycleTime = 0x00000000;

  systick_config();

}

//
//
//
void Sleep(void)
{
   __WFI();
}

//
//
//
void SysTick_Handler(void)
{
  systick_counter++;
  u8SysTicks ++;

  if (stClocks.bCycleOvrFlag == true)
  {
    stClocks.u32OvrCycleTime += CLOCKS_PER_SYSTICK;
  }

  if (systick_counter % SYSTICKS_PER_LOOP == 0)
  {
    // Set the Cycle Time Flag
    stClocks.bCycleTimeFlag = true;
    __SEV();
  }
}

//
//  returns the current value of the SysTick Timer (counter)
//
uint32_t u32GetTick(void)
{
  return (SysTick->VAL);
}

uint32_t u32GetSysTick(void)
{
  return (systick_counter);
}

void WaitForCycleTime(void)
{
  CheckForTimerOverrun();

  while (stClocks.bCycleTimeFlag == false)
  {
    Sleep();
    __no_operation();
    
  }

  ClearCycleTimeFlag();
  StartLoopOvrDetection();
}

///
// @brief   return Pclk for timers
// @param   TIMER
// @return  u32 clock in Hz.
// If the APBx Pre-scaler is 1, timers run at APBx Clk, in any other case,
// they run at x2 the APBx Clk
uint32_t u32GetTimerClock(uint32_t timer)
{
  uint32_t clock = 0;
  switch(timer)
  {
  case TIMER1:
  case TIMER2:
  case TIMER3:
  case TIMER4:
  case TIMER5:
  case TIMER6:
  case TIMER11:
  case TIMER12:
  case TIMER13:
    if ((RCU_CFG0 & RCU_CFG0_APB1PSC) == RCU_APB1_CKAHB_DIV1)
      clock = stSystemClocks.PCLK1_Frequency;
    else
      clock = 2 * stSystemClocks.PCLK1_Frequency;
    break;
  case TIMER0:
  case TIMER7:
  case TIMER8:
  case TIMER9:
  case TIMER10:
    if ((RCU_CFG0 & RCU_CFG0_APB2PSC) == RCU_APB2_CKAHB_DIV1)
      clock = stSystemClocks.PCLK2_Frequency;
    else
      clock = 2 * stSystemClocks.PCLK2_Frequency;
    break;
  default:
    DEBUG_BREAK();
    clock = 0;
    break;
  }
  return(clock);
}

///
// @brief populate the System Clock struct
// @pararm none
// @return none
//
void GetSystemClocks(void)
{
  stSystemClocks.SYSCLK_Frequency = rcu_clock_freq_get(CK_SYS);
  stSystemClocks.HCLK_Frequency = rcu_clock_freq_get(CK_AHB);
  stSystemClocks.PCLK1_Frequency = rcu_clock_freq_get(CK_APB1);
  stSystemClocks.PCLK2_Frequency = rcu_clock_freq_get(CK_APB2);
  //pSystemClocks->ADCCLK_Frequency = rcu_clock_freq_get(CK_ADC);
  stSystemClocks.TIMER1_Frequency = u32GetTimerClock(TIMER1);
  stSystemClocks.TIMER2_Frequency = u32GetTimerClock(TIMER2);
  stSystemClocks.TIMER5_Frequency = u32GetTimerClock(TIMER5);
  stSystemClocks.TIMER6_Frequency = u32GetTimerClock(TIMER6);
}

