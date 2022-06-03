#include <atmel_start.h>
#include <samd21j18a.h>

#include "memory_map.h"

/* Read the reason we need naked in the function prototype declaration: https://gcc.gnu.org/onlinedocs/gcc/ARM-Function-Attributes.html#index-naked-function-attribute_002c-ARM */
static void start_app(void *pc, void *sp) __attribute__((naked));

/* The parameters are mapped from C to ASM following the Procedure Call Standard for the Arm Architecture:
 * 8.2 ArgumentPassingConventions
 *   The argument list for a subroutine call is formed by taking the user arguments in the order in which they are specified
 * r1 = sp
 * r0 = pc
 */
static void start_app(void *pc, void *sp)
{
  __asm("           \n\
          msr msp, r1 \n\
          bx r0       \n\
    ");
}

int main(void)
{
  /* TEST CODE to visualize the bootloader running */
  /* Initializes MCU, drivers and middleware */
  atmel_start_init();

  for (int i = 0; i < 10; i++)
  {
    for (long i = 0; i < 250 * 100 * 48; ++i)
    {
      asm("NOP");
    }

    gpio_toggle_pin_level(LED);
  }

  gpio_set_pin_level(LED, true);
  /* END TEST CODE  */

  DeviceVectors *app_vectors = (DeviceVectors *)&__rom_start__;   // Needs samd21j18a.h and memory_map.h
  start_app(app_vectors->pfnReset_Handler, app_vectors->pvStack); // The program counter receive the address of the reset handler of the application, the stack pointer shoudl be the one of the application (application is stored in ROM, see memory_map.ld)

  // should never be reached
  while (1)
    ;
}