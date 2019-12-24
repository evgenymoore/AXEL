#ifndef __ADC_CONTROLLER_H
#define __ADC_CONTROLLER_H

#include "stm32l071xx.h"
#include "stm32l0xx_hal.h"
#include "stdint.h"

void adc_init(void);
void dma_init(uint32_t * memory);
void tim6_init(void);
void tim6_activate(void);
void tim2_init(void);
void tim2_activate(void);

#endif /* __ADC_CONTROLLER_H */