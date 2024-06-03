#include    "Hardware.h"

//
//  The STM32F1xx factory programmed flash size value. This indicates the total
//  size of flash memory in KB.
//  See section 23.1.1 of the STM32F100 Reference Manual.
#define F_SIZE_ADDRESS              ((__I uint16_t *) 0x1FFFF7E0)
#define F_SIZE                      (*F_SIZE_ADDRESS)


uint32_t deviceID, productID;
reset_event_code_en resetReason;
bool  bPwrGood = true;      // Vdd state

//
// functions
//
static void InitPVD(void);

//
//
reset_event_code_en enGetResetReason(void)
{
        
  reset_event_code_en enReason = ARM32_UNKNOWN_RESET;
  if (rcu_flag_get(RCU_FLAG_FWDGTRST))
    enReason = ARM32_WATCHDOG_RESET;      // Independent Watchdog
  else if (rcu_flag_get(RCU_FLAG_WWDGTRST))
    enReason = ARM32_WATCHDOG_RESET;      // Window Watchdog
  else if (rcu_flag_get(RCU_FLAG_SWRST))
    enReason = ARM32_SOFTWARE_RESET;      // Self (software)
  else if (rcu_flag_get(RCU_FLAG_PORRST))
    enReason = ARM32_POWER_ON_RESET;      // Power-on
  else if (rcu_flag_get(RCU_FLAG_EPRST))
    enReason = ARM32_EXTERNAL_RESET;      // External pin reset
//  else if (rcu_flag_get(RCU_FLAG_LPRST))
//    enReason = ARM32_LOW_POWER_RESET;      // Low power
//  else if (rcu_flag_get(RCU_FLAG_OBLRST))
//    enReason = ARM32_OPTION_BYTE_RESET;   // Option byte reset
//  else if (rcu_flag_get(RCU_FLAG_V12RST))
//    enReason = ARM32_OPTION_BYTE_RESET;   // V12 domain power reset
  else
    enReason = ARM32_UNKNOWN_RESET;       // Unknown reset

  rcu_all_reset_flag_clear();

#ifdef FAULT_MSG
  printf("reset=%d\n",enReason);
#endif
  return(enReason);
}

void InitHardware(void)
{

  resetReason = enGetResetReason();

  productID = FMC_PID;      // "product ID" in FlashMemoryController
  deviceID  = dbg_id_get();  // should be 0x414
  

  // enable the debug register:
  dbg_low_power_enable(DBG_LOW_POWER_SLEEP);
   
  /* enable AF and setup JTAG to allow normal use of PA15/PB3/PB4 (SPI2) */
  rcu_periph_clock_enable(RCU_AF);
  gpio_pin_remap_config(GPIO_SWJ_SWDPENABLE_REMAP, ENABLE);

  InitWatchdog();
  InitNVIC();

  /* Initialize all configured peripherals */
  GPIO_Init();

   /* PVD Configuration */
  InitPVD();
  // do an initial read of the PVD state:
  if (pmu_flag_get(PMU_FLAG_LVD))
    bPwrGood = false;
  else
    bPwrGood = true;

} // end InitHardware()

//
//
//
static void InitPVD(void)
{
  // Enable the Clock for the Power Module
  rcu_periph_clock_enable(RCU_PMU);

  // PWR_PVDLevelConfig(PWR_PVDLevel_2V9);
  pmu_lvd_select(PMU_LVDT_5);

  exti_interrupt_flag_clear(EXTI_16);
  /* configure EXTI_16  */
  exti_init(EXTI_16, EXTI_INTERRUPT, EXTI_TRIG_BOTH);
}

// end of Hardware.c
