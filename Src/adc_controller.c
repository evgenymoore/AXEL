/* ФАЙЛ ИНИЦИАЛИЗАЦИИ АЦП И ТАЙМЕРА */

#include "adc_controller.h"

/* функция инициализации модуля АЦП */
void adc_init(void)
{
  /* тактирование модуля АЦП */
  RCC->APB2ENR |= RCC_APB2ENR_ADCEN;

  /* калибровка АЦП */
  ADC1->CR |= ADC_CR_ADCAL;      
  while (ADC1->CR & ADC_CR_ADCAL);
  
  /* активация триггера по TIM6*/
  //ADC1->CFGR1 |= ADC_CFGR1_EXTEN_0;
  
  /* активация триггера по TIM2*/
  ADC1->CFGR1 |= ADC_CFGR1_EXTEN_0 | ADC_CFGR1_EXTSEL_1;
  
  /* прерывания АЦП */
  //ADC1->IER |= ADC_IER_OVRIE | ADC_IER_EOCIE | ADC_IER_EOSEQIE;
  //регистрация прерывания АЦП в модуле прерываний NVIC
  //HAL_NVIC_SetPriority(ADC1_COMP_IRQn, 0, 0); 
  //HAL_NVIC_EnableIRQ(ADC1_COMP_IRQn);  
  
  /* разрешение АЦП на работу с DMA*/
  ADC1->CFGR1 |= ADC_CFGR1_DMAEN | ADC_CFGR1_DMACFG;
  
  /* выбор каналов АЦП */
  //ADC-X ADC-Y ADC-Z
  ADC1->CHSELR |= ADC_CHSELR_CHSEL0 | ADC_CHSELR_CHSEL1 | ADC_CHSELR_CHSEL2;
  
  //ADC-P
  ADC1->CHSELR |= ADC_CHSELR_CHSEL7;
  
  /* время сэмплирования всех каналов АЦП */
  //время сэмплирования - 7.5 циклов
  ADC1->SMPR |= 2; 
  
  /* включение АЦП */
  ADC1->CR |= ADC_CR_ADEN;
  
  /* запуск преобразования АЦП */
  ADC1->CR |= ADC_CR_ADSTART;

  /* проверка на готовность к преобразованию АЦП */
  while (!(ADC1->ISR && ADC_ISR_ADRDY));
}

/* функция инициализации DMA для АЦП */
void dma_init(uint32_t * memory)
{
  /* тактирование модуля DMA */
  RCC->AHBENR |= RCC_AHBENR_DMA1EN;
   
  /* адрес периферийного регистра */
  DMA1_Channel1->CPAR = (uint32_t) (&(ADC1->DR));
  
  /* адрес регистра памяти */
  DMA1_Channel1->CMAR = (uint32_t) (memory);
  
  /* количество передаваемых данных */
  DMA1_Channel1->CNDTR = 4;
  
  /* инкрементирование */
  DMA1_Channel1->CCR |= DMA_CCR_MINC;
  
  /* круговой режим */
  DMA1_Channel1->CCR |= DMA_CCR_CIRC;
  
  /* размеры данных из периферии и памяти */
  DMA1_Channel1->CCR |= DMA_CCR_PSIZE_0 | DMA_CCR_MSIZE_0;
  
  /* прерывания DMA */
  DMA1_Channel1->CCR |= DMA_CCR_TEIE | DMA_CCR_TCIE;
  HAL_NVIC_SetPriority(DMA1_Channel1_IRQn, 0, 0); 
  HAL_NVIC_EnableIRQ(DMA1_Channel1_IRQn);
  
  /* активация канала DMA */
  DMA1_Channel1->CCR |= DMA_CCR_EN;
}

/* функция инициализации таймера TIM6 для АЦП */
void tim6_init(void) 
{
  /* тактирование таймера */
  RCC->APB1ENR |= RCC_APB1ENR_TIM6EN;
  
  TIM6->CR1 |= TIM_CR1_ARPE;
  
  /* активация триггера */
  TIM6->CR2 |= TIM_CR2_MMS_1;
  
  /* prescaler value */
  TIM6->PSC = 32000 - 1;
  
  /* ARR value */
  TIM6->ARR = 100 - 1;
  
  /* регистрация генерации событий */
  TIM6->EGR |= TIM_EGR_UG;
  
  TIM6->SR = 0; 
   
  //TIM6->DIER |= TIM_DIER_UIE; 
  /* прерывания таймера */
  //HAL_NVIC_SetPriority(TIM6_DAC_IRQn, 0, 0); 
  //HAL_NVIC_EnableIRQ(TIM6_DAC_IRQn); 
}

/* функция запуска таймера TIM6 */
void tim6_activate(void)
{
  /* запуск отсчета таймера */
  TIM6->CR1 |= TIM_CR1_CEN;
}

void tim2_init(void) 
{
  /* тактирование таймера */
  RCC->APB1ENR |= RCC_APB1ENR_TIM2EN;
  
  TIM2->CR1 |= TIM_CR1_ARPE;
  
  /* активация триггера */
  TIM2->CR2 |= TIM_CR2_MMS_1;
  
  /* prescaler value */
  TIM2->PSC = 32000 - 1;
  
  /* ARR value */
  TIM2->ARR = 10 - 1;
  
  /* регистрация генерации событий */
  TIM2->EGR |= TIM_EGR_UG;
  
  TIM2->SR = 0; 
   
  //TIM2->DIER |= TIM_DIER_UIE; 
  /* прерывания таймера */
  //HAL_NVIC_SetPriority(TIM2_DAC_IRQn, 0, 0); 
  //HAL_NVIC_EnableIRQ(TIM2_DAC_IRQn); 
}

/* функция запуска таймера TIM2 */
void tim2_activate(void)
{
  /* запуск отсчета таймера */
  TIM2->CR1 |= TIM_CR1_CEN;
}