#include "at32m412_416.h"
#include "at32m412_416_crm.h"
#include "at32m412_416_gpio.h"

static void delay_ms(uint32_t ms)
{
    SysTick->LOAD = SystemCoreClock / 1000 - 1;
    SysTick->VAL = 0;
    SysTick->CTRL = SysTick_CTRL_CLKSOURCE_Msk |
                    SysTick_CTRL_ENABLE_Msk;

    for (uint32_t i = 0; i < ms; i++)
    {
        while ((SysTick->CTRL & SysTick_CTRL_COUNTFLAG_Msk) == 0)
        {
        }
    }

    SysTick->CTRL = 0;
}

int main(void)
{

  gpio_init_type gpio_init_struct;

  crm_periph_clock_enable(CRM_GPIOC_PERIPH_CLOCK, TRUE);

  gpio_default_para_init(&gpio_init_struct);
  gpio_init_struct.gpio_pins = GPIO_PINS_13;
  gpio_init_struct.gpio_mode = GPIO_MODE_OUTPUT;
  gpio_init_struct.gpio_out_type = GPIO_OUTPUT_PUSH_PULL;
  gpio_init_struct.gpio_pull = GPIO_PULL_NONE;
  gpio_init_struct.gpio_drive_strength = GPIO_DRIVE_STRENGTH_STRONGER;
  gpio_init(GPIOC, &gpio_init_struct);

  while (1)
  {
    gpio_bits_toggle(GPIOC, GPIO_PINS_13);
    delay_ms(250U);
  }

  return 0;
}
