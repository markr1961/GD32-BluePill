#ifndef     _PIN_DEFS_H
#define     _PIN_DEFS_H

//
//  INCLUDE FILES
//

#include "GPIO_Init.h"

//  Define the usage of the STM32F103C8 port A signals.

//#define   _PA8                GPIO_PIN_8  // (not used)

//  Define the usage of the STM32F103C8 port B signals.

//#define   BOOT1_PB2                   GPIO_PIN_2  // Tied to Vss
#define     USART_TXD_PB6       GPIO_PIN_6  // USART0
#define     USART_RXD_PB7       GPIO_PIN_7  // USART0

//  Define the usage of the STM32F103C8 port C signals.

#define     LED_PC13            GPIO_PIN_13
//#define   OSC32_IN_PC14         GPIO_PIN_14 // RTC 32kHz crystal!
//#define   OSC32_OUT_PC15        GPIO_PIN_15 // RTC 32kHz crystal!

//  Define macro constants for use with the ST Peripheral Firmware Library
//  functions such as GPIO_ReadInputDataBit(), GPIO_ResetBits() and GPIO_SetBits().
//  These take TWO arguments: the port and bit(s). The macro constants here are
//  designed to be used to set both arguments at once.
//  This makes the definitions LOOK strange and its certainly an unusual way
//  to the use the preprocessor but I think it makes the code more readable
//  and less prone to errors (port and bit in one definition not two).

#define     USART_TXD          GPIOB,USART_TXD_PB6
#define     USART_RXD          GPIOB,USART_RXD_PB7
//#define                        GPIOA,_PA8

//#define                        GPIOB,_PB0
//#define                        GPIOB,_PB1
//#define   BOOT1                GPIOB,BOOT1_PB2
//#define                        GPIOB,_PB3
//#define                        GPIOB,_PB4
//#define                        GPIOB,_PB5
//#define                        GPIOB,_PB9

//#define                        GPIOC,_PC0
//#define                        GPIOC,_PC1
//#define                        GPIOC,_PC2
//#define                        GPIOC,_PC3
//#define                        GPIOC,_PC4
//#define                        GPIOC,_PC5
#define     LED                GPIOC,LED_PC13
//#define   OSC32_IN             GPIOC,OSC32_IN_PC14
//#define   OSC32_OUT            GPIOC,OSC32_OUT_PC15

//  STM32F1xx factory programmed unique chip ID registers (96-bits total).
//  See section 28.2 of the STM32F1xx Reference Manual.
#define     U_ID_31_00_ADDRESS          ((__I uint32_t *) 0x1FFFF7E8)
#define     U_ID_63_32_ADDRESS          ((__I uint32_t *) 0x1FFFF7EC)
#define     U_ID_95_64_ADDRESS          ((__I uint32_t *) 0x1FFFF7F0)

#define     U_ID_31_00                  (*U_ID_31_00_ADDRESS)
#define     U_ID_63_32                  (*U_ID_63_32_ADDRESS)
#define     U_ID_95_64                  (*U_ID_95_64_ADDRESS)

#endif // _PIN_DEFS_H
