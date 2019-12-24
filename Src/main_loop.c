/* ГЛАВНЫЙ ФАЙЛ, ВКЛЮЧАЮЩИЙ ПРОВЕРКУ ФЛАГА И ПОСЫЛКУ ДАННЫХ*/

#include "main_loop.h"

uint16_t memory_buffer[4];
uint8_t resistance_value = 0x80;

_Bool flag = false;

int run(void)
{
  //tim6_init();
  tim2_init();
  dma_init((uint32_t *) memory_buffer);
  adc_init(); 
  spi_2_init(resistance_value);
  //tim6_activate();
  tim2_activate();
  while (1)
  {
    if (flag == true)
    {
      GPIOC->ODR ^= TEST1_Pin ^ TEST2_Pin;
      send_message(memory_buffer[0], memory_buffer[1], memory_buffer[2], memory_buffer[3]);
      flag = false;
    }
  }
}