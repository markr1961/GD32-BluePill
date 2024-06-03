#include <gd32f30x.h>  // required for "NVIC_reset"
#include "NVIC.h"
#include "ICF_Symbols.h"
#include "Hardware.h"  // DEBUG_BREAK()

typedef struct
{
  uint8_t             u8Flag;   // For RCC_GetFlagStatus()
  reset_event_code_en enReason;
}  reset_st;

void __exit(int arg)
{
  DEBUG_BREAK();

  // shutting down, so prevent any interrupts that might affect it
  __disable_interrupt();
  // Software Reset
  NVIC_SystemReset();
  
  (void)arg;
}

void InitNVIC(void)
{
  /* EXTI10_15_IRQn interrupt configuration */
  // button
  // NVIC_SetPriority(EXTI10_15_IRQn, 5);
  // NVIC_EnableIRQ(EXTI10_15_IRQn);

  /* USART0_IRQn interrupt configuration */
  // NVIC_SetPriority(USART0_IRQn, 7);
  // NVIC_EnableIRQ(USART0_IRQn);

  /* LVD_IRQn interrupt configuration */
  //NVIC_SetPriority(LVD_IRQn, 9);
  //NVIC_EnableIRQ(LVD_IRQn);

  // Enable division by zero trap.
  SCB->CCR |= SCB_CCR_DIV_0_TRP_Msk;

}

// eof NVIC.c
