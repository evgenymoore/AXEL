#include "spi_2_init.h"

/* функция передачи данных по SPI */
void spi_2_init(uint8_t resistance_value)
{
  /* BIT CHIP SELECT = 0 */
  GPIOB->ODR &= ~SPI2_CS_Pin;
  
  /* передача адресных битов по MOSI */
  uint8_t address_bit = 2;
  while (address_bit > 0)
  {
    /* address bit's = 0  */      
    GPIOB->ODR &= ~SPI2_MOSI_Pin;
    HAL_Delay(1);
    
    /* активация тактирование CLK - выставление уровня на CLK */
    GPIOB->ODR |= SPI2_SCK_Pin;
    HAL_Delay(1);
    
    /* снятие уровня на CLK */
    GPIOB->ODR &= ~SPI2_SCK_Pin;
    
    address_bit--;
  }
  
  /* цикл передачи данных по MOSI */
  for (int8_t shift = 7; shift >= 0; shift--)
  {
    /* resistance_value >> shift - сдвиг старшего бита и установка уровня на MOSI */
    (resistance_value >> shift) & 0x1 ? (GPIOB->ODR |= SPI2_MOSI_Pin) : (GPIOB->ODR &= ~SPI2_MOSI_Pin);
    HAL_Delay(1);
    
    /* активация тактирование CLK - выставление уровня на CLK */
    GPIOB->ODR |= SPI2_SCK_Pin;
    HAL_Delay(1);
    
    /* снятие уровня на CLK */
    GPIOB->ODR &= ~SPI2_SCK_Pin;
  }
  
  /* BIT MOSI = 0 */
  GPIOB->ODR &= ~SPI2_MOSI_Pin;
  
  /* BIT CHIP SELECT = 1 */
  GPIOB->ODR |= SPI2_CS_Pin;
}

/* функция передачи данных по SPI */
void gain_change(uint8_t resistance_value)
{
  
}