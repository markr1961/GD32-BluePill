
//
#include "Hardware.h"

#ifdef DEBUG
static clock_t LastWdogPat = 0;
#endif

//
//
//
void InitWatchdog(void)
{
  //Configure the Debug Interface so that it can stop the Watchdog
  dbg_periph_enable(DBG_FWDGT_HOLD);

  /* enable IRC40K */
  rcu_osci_on(RCU_IRC40K);
  /* wait till IRC40K is ready */
  rcu_osci_stab_wait(RCU_IRC40K);
  
  /* enable write access to FWDGT_PSC and FWDGT_RLD registers.
     FWDGT counter clock: 40KHz(IRC40K) / 64 = 0.625 KHz */
  fwdgt_config(625, FWDGT_PSC_DIV64); // set for ~1 second.
  fwdgt_enable();
}

//
//
//
void PatWatchdog(void)
{
  fwdgt_counter_reload();

#ifdef DEBUG
  LastWdogPat = systick_counter;
#endif

}
