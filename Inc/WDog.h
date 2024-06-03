///////////////////////////////////////////////////////////////////////////////
//                                                                           //
//            H U B B E L L   B U I L D I N G  A U T O M A T I O N           //
//                                                                           //
//            (C) Copyright 2011 Hubbell Building Automation, Inc.           //
//                            All Rights Reserved.                           //
//                                                                           //
///////////////////////////////////////////////////////////////////////////////
// MODULE:      WDog.h                                                       //
// PROJECT:     WiHubb Smart Pack                                            //
// DESCRIPTION: This file contains the function prototypes and globals for   //
//              the Independent Watchdog Timer on the STM32F100x. This is a  //
//              direct port of HOWL v0.05C code for IFM.                     //
// AUTHOR:      Ron Cummings-Kralik                                          //
// HISTORY:     02/22/2011 - Initially Created - RJCK                        //
//              xx/xx/xxxx - Modification desc...                            //
///////////////////////////////////////////////////////////////////////////////
//
//  MODULE DECLARATION
//
#ifndef _WDOG_H
#define _WDOG_H
//
//  PRAGMA'S AND CONDITIONAL CONTROL
//

//
//  INCLUDE FILES
//

//
// EXPORTED MACRO CONSTANTS
//

//
// EXPORTED MACRO FUNCTIONS
//

//
// EXPORTED TYPES
//

//
// EXPORTED VARIABLES
//

//
// EXPORTED FUNCTIONS
//
extern void InitWatchdog(void);
extern void PatWatchdog(void);
#endif
