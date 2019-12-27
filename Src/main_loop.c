/* ГЛАВНЫЙ ФАЙЛ, ВКЛЮЧАЮЩИЙ ПРОВЕРКУ ФЛАГА И ПОСЫЛКУ ДАННЫХ*/

#include "main_loop.h"

uint16_t memory_buffer[4];
uint8_t resistance_value = 0x0;
_Bool flag = true;

unsigned resistance_upd_cnt = 0;

int run(void)
{
  //tim6_init();
  tim2_init();
  dma_init((uint32_t *) memory_buffer);
  adc_init(); 
  //tim6_activate();
  tim2_activate();
  mcs_tim_init();
  while (1)
  {
    //spi_2_init(resistance_value);
    //if (resistance_value == 0xFF)
      //resistance_value = 0x0;
    if (flag == true)                           // Run every 10ms
    {
      //GPIOC->ODR ^= TEST1_Pin ^ TEST2_Pin;
      send_message(memory_buffer[0], memory_buffer[1], memory_buffer[2], memory_buffer[3]);
      flag = false;
      resistance_upd_cnt += 10;
      if(resistance_upd_cnt == 100)
      {
        resistance_upd_cnt = 0;
        spi_2_init(resistance_value += 5);
        GPIOC->ODR ^= TEST1_Pin ^ TEST2_Pin;
        if (resistance_value == 0xFF)
          resistance_value = 0x0;
      }
    }
  }
}