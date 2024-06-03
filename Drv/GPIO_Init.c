//
#include  "GPIO_Init.h"
#include  "Pin_Defs.h"
//
//
void GPIO_Init(void)
{
  /*----------------------------------------------------------------------------
  Configure GPIO

  USART pins are handled in USART_Init()
  SPI GPIO is handled in InitSPI()
  I2C GPIO is handled in InitI2C()
  VoltageZeroCross input is always init'ed with a pull-up.
  Occ input is inited with pull down here. It will be re-init'ed later on FM-O.
  Relay control outputs are left at default on FM-LV
  ----------------------------------------------------------------------------*/

  /* GPIO Ports Clock Enable */
  // rcu_periph_clock_enable(RCU_GPIOA);
  // rcu_periph_clock_enable(RCU_GPIOB);
  rcu_periph_clock_enable(RCU_GPIOC);

  /* make sure pins that need to start in a specific state are handled */
  //gpio_bit_reset(DBGOUT1);
  //gpio_bit_reset(DBGOUT2);

  // port A inputs:
  //gpio_init(GPIOA, GPIO_MODE_IPU, GPIO_OSPEED_2MHZ, some pins);
  // port A outputs:
  //gpio_init(GPIOA, GPIO_MODE_OUT_PP,GPIO_OSPEED_2MHZ, some pins);

  // port B inputs:
  //gpio_init(GPIOB, GPIO_MODE_IPU, GPIO_OSPEED_2MHZ, BUTTON_Pin);
  //gpio_init(GPIOB, GPIO_MODE_IPD, GPIO_OSPEED_2MHZ, OCC_IN_Pin);
  // port B outputs:
  //gpio_init(GPIOB,GPIO_MODE_OUT_PP,GPIO_OSPEED_2MHZ, some pins);

  // port C inputs:
  //gpio_init(GPIOC, GPIO_MODE_IPU, GPIO_OSPEED_2MHZ, some pins);
  // port C outputs:
  gpio_init(GPIOC, GPIO_MODE_OUT_PP, GPIO_OSPEED_2MHZ, LED_PC13);


  /* configure SPI /CS NSS (PA15) */
  //gpio_bit_set(SPI_FLASH_CS);  // set /CS high first.
  //gpio_init(SPI_nCS_GPIO_Port, GPIO_MODE_OUT_PP, GPIO_OSPEED_50MHZ, SPI_nCS_Pin);

}