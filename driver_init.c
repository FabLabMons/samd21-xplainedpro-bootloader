/*
 * Code generated from Atmel Start.
 *
 * This file will be overwritten when reconfiguring your Atmel Start project.
 * Please copy examples or other code you want to keep to a separate file
 * to avoid losing it when reconfiguring.
 */

#include "driver_init.h"
#include <peripheral_clk_config.h>
#include <utils.h>
#include <hal_init.h>
#include <hpl_gclk_base.h>
#include <hpl_pm_base.h>

void USR_BTN_IRQ_init(void)
{
  _gclk_enable_channel(EIC_GCLK_ID, CONF_GCLK_EIC_SRC);

  // Set pin direction to input
  gpio_set_pin_direction(USR_BTN, GPIO_DIRECTION_IN);

  gpio_set_pin_pull_mode(USR_BTN,
                         // <y> Pull configuration
                         // <id> pad_pull_config
                         // <GPIO_PULL_OFF"> Off
                         // <GPIO_PULL_UP"> Pull-up
                         // <GPIO_PULL_DOWN"> Pull-down
                         GPIO_PULL_OFF);

  gpio_set_pin_function(USR_BTN, PINMUX_PA15A_EIC_EXTINT15);

  ext_irq_init();
}

void system_init(void)
{
  init_mcu();

  USR_BTN_IRQ_init();

  // // GPIO on PA15

  // // Set pin direction to input
  // gpio_set_pin_direction(USR_BTN, GPIO_DIRECTION_IN);

  // gpio_set_pin_pull_mode(USR_BTN,
  //                        // <y> Pull configuration
  //                        // <id> pad_pull_config
  //                        // <GPIO_PULL_OFF"> Off
  //                        // <GPIO_PULL_UP"> Pull-up
  //                        // <GPIO_PULL_DOWN"> Pull-down
  //                        GPIO_PULL_OFF);

  // gpio_set_pin_function(USR_BTN, GPIO_PIN_FUNCTION_OFF);

  // GPIO on PB30

  gpio_set_pin_level(LED,
                     // <y> Initial level
                     // <id> pad_initial_level
                     // <false"> Low
                     // <true"> High
                     false);

  // Set pin direction to output
  gpio_set_pin_direction(LED, GPIO_DIRECTION_OUT);

  gpio_set_pin_function(LED, GPIO_PIN_FUNCTION_OFF);
}
