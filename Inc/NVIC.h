
#ifndef _NVIC_H
#define _NVIC_H

//  Non-ANSI Standard C codes for exit(). These are used by the exception
//  handlers to log reset reason.
#define     EXIT_NMI                    2
#define     EXIT_HARD_FAULT             3
#define     EXIT_BUS_FAULT              4
#define     EXIT_USAGE_FAULT            5
#define     EXIT_MEM_FAULT              6

void InitNVIC(void);
void exit(int arg);

#endif
