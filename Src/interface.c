/* ФАЙЛ ОТПРАВКИ БУФЕРА В ТЕРМИНАЛ */

#include "interface.h"

uint8_t uart_buffer[9] = {0xAA};

/* функция отправки*/
void send_message(uint16_t x, uint16_t y, uint16_t z, uint16_t p)
{
  /* заполение буфера для передачи */
  //1-й канал АЦП
  uart_buffer[1] = (uint8_t)(x >> 8);
  uart_buffer[2] = (uint8_t)(x);
  
  //2-й канал АЦП
  uart_buffer[3] = (uint8_t)(y >> 8);
  uart_buffer[4] = (uint8_t)(y);
  
  //3-й канал АЦП
  uart_buffer[5] = (uint8_t)(z >> 8);
  uart_buffer[6] = (uint8_t)(z);  
  
  //4-й канал АЦП
  uart_buffer[7] = (uint8_t)(p >> 8);
  uart_buffer[8] = (uint8_t)(p); 
  
  /* направление передачи данных по UART */
  GPIOA->BSRR |= RE_DE_Pin; //GPIOA->BSRR |= RE_DE_Pin << 16; 
  
  /* передача данных по UART */
  HAL_UART_Transmit(&huart1, uart_buffer, 9, 100);
}
