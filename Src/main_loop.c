/* ГЛАВНЫЙ ФАЙЛ, ВКЛЮЧАЮЩИЙ ПРОВЕРКУ ФЛАГА И ПОСЫЛКУ ДАННЫХ */
#include "main_loop.h"
#include "adc_controller.h"
#include "interface.h"

int run(void)
{
  adc_init();
  tim6_init();
  while (1)
  {
    
  }
}