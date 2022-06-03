#include <atmel_start.h>

volatile bool powerButtonEnabled = true;
volatile bool powerButtonPressed = false;

static void powerButtonPressed_IRQ(void);

static void powerButtonPressed_IRQ(void)
{
  if (powerButtonEnabled)
  {
    powerButtonEnabled = false;
    powerButtonPressed = true;
  }
}

int main(void)
{
  /* Initializes MCU, drivers and middleware */
  atmel_start_init();

  /* Replace with your application code */
  while (1)
  {
    for (long i = 0; i < 250 * 1000 * 48; ++i)
    {
      asm("NOP");
    }

    gpio_toggle_pin_level(LED);
  }
}
