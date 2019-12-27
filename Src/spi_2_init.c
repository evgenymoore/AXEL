#include "spi_2_init.h"

#define MCS_TIM TIM7


void mcs_tim_init(void)
{
    // Interface timer settings
    RCC->APB1ENR |= RCC_APB1ENR_TIM7EN;
    
    MCS_TIM->PSC = (2)-1;
    MCS_TIM->CR1 = TIM_CR1_OPM;
    
    MCS_TIM->EGR |= TIM_EGR_UG;             // Update Event
    __NOP();
    __NOP();
    
    MCS_TIM->SR &= ~(TIM_SR_UIF);         /* Clear pending flag */ 
}

/* Blocking delay. 1500uc maximum */
void delay_mcs(uint32_t mcs)
{
    MCS_TIM->ARR = (SystemCoreClock/2000000) * mcs;
    MCS_TIM->CR1 |= TIM_CR1_CEN;
    
    while((MCS_TIM->SR & TIM_SR_UIF) == 0){}
    MCS_TIM->SR &= ~TIM_SR_UIF;
}




/* функция передачи данных по SPI */
void spi_2_init(uint8_t resistance_value)
{
  /* BIT CHIP SELECT = 0 */
  GPIOB->ODR &= ~SPI2_CS_Pin;
  
  /* передача адресных битов по MOSI */
  for (uint8_t address_bit = 2; address_bit > 0; address_bit--)
  {
    /* address bit's = 0  */      
    GPIOB->ODR &= ~SPI2_MOSI_Pin;
    //HAL_Delay(1);
    delay_mcs(10);
    
    /* активация тактирование CLK - выставление уровня на CLK */
    GPIOB->ODR |= SPI2_SCK_Pin;
   // HAL_Delay(1);
    delay_mcs(10);
    
    /* снятие уровня на CLK */
    GPIOB->ODR &= ~SPI2_SCK_Pin;
  }
  
  /* цикл передачи данных по MOSI */
  for (int8_t shift_bit = 7; shift_bit >= 0; shift_bit--)
  {
    /* resistance_value >> shift - сдвиг старшего бита и установка уровня на MOSI */
    (resistance_value >> shift_bit) & 0x1 ? (GPIOB->ODR |= SPI2_MOSI_Pin) : (GPIOB->ODR &= ~SPI2_MOSI_Pin);
   // HAL_Delay(1);
    delay_mcs(10);
    
    /* активация тактирование CLK - выставление уровня на CLK */
    GPIOB->ODR |= SPI2_SCK_Pin;
   // HAL_Delay(1);
    delay_mcs(10);
    
    /* снятие уровня на CLK */
    GPIOB->ODR &= ~SPI2_SCK_Pin;
  }
 
  /* BIT MOSI = 0 */
  GPIOB->ODR &= ~SPI2_MOSI_Pin;
  
  /* BIT CHIP SELECT = 1 */
  GPIOB->ODR |= SPI2_CS_Pin;
}