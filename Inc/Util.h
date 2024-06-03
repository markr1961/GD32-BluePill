// util.h

#ifndef _UTIL_H_
#define _UTIL_H_

#include <time.h>
#include "Hardware.h"

#ifdef __cplusplus
extern "C" {
#endif

// =======================================================================

#if !defined(STM32F100) && !defined(STM32F103)
#define STM32F103
#endif

//#if defined(STM32F100)
//#elif defined(STM32F103)
//#else
// #error CPU type not defined!
//#endif

// =======================================================================
// STM32 system clock stuff

//  The IAR Embedded Workbench for ARM 5.x compiler defines 'CLOCKS_PER_SEC'
//  in time.h. Their value is not correct in this application so its redefined
//  here (for clock()). Note that for the #undef to work this header MUST be
//  included AFTER time.h.

#undef  CLOCKS_PER_SEC
#define CLOCKS_PER_SEC              1000    // 1kHz (1mS interrupts)

// Initialize the STM32F10x system clocks
extern void stm32_system_clocks_init(void);

//----------------------------------------------------------------------------

extern void delay_ms(clock_t ms);
extern void stm32_systick_disable(void);
extern void stm32_systick_init(void);

//----------------------------------------------------------------------------

//  The onchip flash starts at this address in all STM32F1xx devices. Note that
//  its also mirrored at 0x00000000 for the Cortex-M3 core.

#define FLASH_START_ADDRESS         ((void *) 0x08000000)

//  The STM32F1xx factory programmed flash size value. This indicates the total
//  size of flash memory in KB.
//  See section 23.1.1 of the STM32F100 Reference Manual.

#define F_SIZE_ADDRESS              ((__I uint16_t *) 0x1FFFF7E0)
#define F_SIZE                      (*F_SIZE_ADDRESS)

//  The flash page size (and total flash size) depend on the device type. See
//  Tables 2-3 in the STM32F100 Reference Manual.

enum {
#if defined(STM32F10X_LD) || defined(STM32F10X_MD) || defined(STM32F10X_LD_VL) || defined(STM32F10X_MD_VL)
    STM32_FLASH_PAGE_SIZE = 1024,
#elif defined(STM32F10X_HD) || defined(STM32F10X_CL) || defined(STM32F10X_XL) || defined(STM32F10X_HD_VL)
    STM32_FLASH_PAGE_SIZE = 2048,
#else
    #error Undefined CPU flash page size!
#endif
};

//
//  EXPORTED FUNCTIONS
//

// Initialize the debug serial port.
extern void debug_interface_init(void);

// Force debug output to finish transmitting on USART1
extern void debug_flush(void);


// =======================================================================
// reboot stuff

extern void deinit_system(void);
extern void reboot_system(void);

//----------------------------------------------------------------------------

// stuff to move out of main:
/*
extern uint32_t *app_flash_start;
extern uint32_t *app_flash_end;
progress_bar, led_error, general LED state
*/

#ifdef __cplusplus
} // extern "C"
#endif // __cplusplus

#endif // _UTIL_H_
