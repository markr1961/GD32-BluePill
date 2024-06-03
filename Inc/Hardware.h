
#ifndef     _HARDWARE_H
#define     _HARDWARE_H

#ifdef    DEBUG
//  #include "Debug_Interface.h"
#endif

#include    <gd32f30x.h>
#include    <time.h>
#include    <string.h>    //memcpy

#include  "Pin_defs.h"
#include  "GPIO_Init.h"
#include  "NVIC.h"

#include  "Clocks.h"
#include  "WDog.h"

#define   HEART_BEAT_RATE   500   // mSec

//
//
//
typedef enum
{
  ARM32_POWER_ON_RESET,
  ARM32_EXTERNAL_RESET,
  ARM32_SOFTWARE_RESET,
  ARM32_LOW_POWER_RESET,
  ARM32_WATCHDOG_RESET,
  ARM32_UNKNOWN_RESET
} reset_event_code_en;

#ifdef DEBUG
  #define DEBUG_BREAK() do { __asm("bkpt #0"); } while(0)
  #define DEBUG_NOP()   __no_operation()
  #define STATIC        static
#else
  #define DEBUG_BREAK()
  #define DEBUG_NOP()
  #define STATIC
#endif

void InitHardware(void);

#endif  // _HARDWARE_H
// eof Hardware.h
