/* ФАЙЛ ИНИЦИАЛИЗАЦИИ АЦП И ТАЙМЕРА */
#include "adc_controller.h"
#include "gpio.h"

/* функция инициализации модуля АЦП */
void adc_init(void)
{
  /* тактирование модуля АЦП */
  RCC->APB2ENR |= RCC_APB2ENR_ADCEN;

  /* калибровка АЦП */
  ADC1->CR |= ADC_CR_ADCAL;      
  while (ADC1->CR & ADC_CR_ADCAL);
  
  /* выбор каналов АЦП */
  //время семплирования - 7.5 циклов
  ADC1->SMPR |= 2; 
  
  /* прерывания АЦП */
  ADC1->IER |= ADC_IER_OVRIE;
  //регистрация прерывания АЦП в модуле прерываний NVIC
  HAL_NVIC_SetPriority(ADC1_COMP_IRQn, 0, 0); 
  HAL_NVIC_EnableIRQ(ADC1_COMP_IRQn);  
  
  /* выбор каналов АЦП */
  ADC1->CHSELR |= ADC_CHSELR_CHSEL0 | ADC_CHSELR_CHSEL1 |
    ADC_CHSELR_CHSEL2 | ADC_CHSELR_CHSEL7;
  
  /* прерывания АЦП */
  ADC1->CR |= ADC_CR_ADEN; 
}

/* функция инициализации DMA для АЦП */
void dma_init(uint32_t * memory, uint8_t * data)
{
  /* тактирование модуля DMA */
  RCC->AHBENR |= RCC_AHBENR_DMAEN;
  
  /* адрес периферийного регистра */
  DMA1_Channel1->CPAR = (uint32_t) (&(ADC1->DR));
  
  /* адрес регистра памяти */
  DMA1_Channel1->CMAR = (uint32_t) (memory);
  
  /* количество передаваемых данных */
  DMA1_Channel1->CNDTR = (uint32_t) data;
  
  /* инкрементирование */
  DMA1_Channel1->CCR |= DMA_CCR_MINC;
  
  /* круговой режим */
  DMA1_Channel1->CCR |= DMA_CCR_CIRC;
  
  /* размеры данных из периферии и памяти */
  DMA1_Channel1->CCR |= DMA_CCR_PSIZE_0 | DMA_CCR_MSIZE_0;
  
  /* прерывания DMA */
  DMA1_Channel1->CCR |= DMA_CCR_TEIE;
  HAL_NVIC_SetPriority(DMA1_Channel1_IRQn, 0, 0); 
  HAL_NVIC_EnableIRQ(DMA1_Channel1_IRQn);
  
  /* разрешение АЦП на работу с DMA*/
  ADC1->CFGR1 |= ADC_CFGR1_DMAEN | ADC_CFGR1_DMACFG;
  
  /* активация канала DMA */
  DMA1_Channel1->CCR |= DMA_CCR_EN;
}

/* функция инициализации таймера TIM6 для АЦП */
void tim6_init(void) 
{
  /* тактирование таймера */
  RCC->APB1ENR |= RCC_APB1ENR_TIM6EN;
  
  /* ARR value */
  TIM6->ARR = 10 - 1;
  
  /* prescaler value */
  TIM6->PSC = 32000 - 1;
  
  /* регистрация генерации событий */
  TIM6->EGR |= TIM_EGR_UG;
  __NOP();
  __NOP(); 
  
  /* сброс статусного регистра */
  TIM6->SR = 0;
  
  /* update interrupt enable */;
  TIM6->DIER |= TIM_DIER_UIE;
  
  /* прерывания таймера */
  HAL_NVIC_SetPriority(TIM6_DAC_IRQn, 0, 0); 
  HAL_NVIC_EnableIRQ(TIM6_DAC_IRQn);
  
  /* активация таймера */
  TIM6->CR1 |= TIM_CR1_CEN;
}