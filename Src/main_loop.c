/* ГЛАВНЫЙ ФАЙЛ, ВКЛЮЧАЮЩИЙ ПРОВЕРКУ ФЛАГА И ПОСЫЛКУ ДАННЫХ */

#include "main_loop.h"

uint16_t memory_buffer[3];

_Bool flag = false;

int run(void)
{
  tim6_init();
  dma_init((uint32_t *) memory_buffer);
  adc_init();
  tim6_activate();
  while (1)
  {
    if (flag == true)
    {
      send_message(memory_buffer[0], memory_buffer[1], memory_buffer[2]);
      flag = false;
    }
  }
}