//
#include "Pin_Defs.h"
#include "GPIO_Init.h"


//
//  GPIO initialization table
//
const io_init_table_st stHwGpioTable[] =
{
    {
        RCC_APB2Periph_GPIOC,
        GPIOC,
        GPIO_Mode_IPU,
        LED_PC13,
        GPIO_Speed_2MHz,
        GPIO_PIN_CONFIG_CHANGABLE
    },
};

const size_t HwGpioSize = sizeof(stHwGpioTable) / sizeof(io_init_table_st);


//
//  USART GPIO initialization table
//
const io_init_table_st stHwUARTGPIOTable[] =
{
    {
        RCC_APB2Periph_GPIOB,
        GPIOB,
        GPIO_Mode_IPU,
        USART_RXD_PB7,
        GPIO_Speed_2MHz,
        GPIO_PIN_CONFIG_CHANGABLE
    },
    {
        RCC_APB2Periph_GPIOA | RCC_APB2Periph_AFIO,
        GPIOA,
        GPIO_Mode_AF_PP,
        USART_TXD_PB6,
        GPIO_Speed_2MHz,
        GPIO_PIN_CONFIG_CHANGABLE
    },
};

const size_t HwUARTGPIOSize = sizeof(stHwUARTGPIOTable) / sizeof(io_init_table_st);
