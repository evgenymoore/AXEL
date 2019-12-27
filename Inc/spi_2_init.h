#ifndef __SPI_2_INIT_H
#define __SPI_2_INIT_H

#include "gpio.h"

extern uint8_t resistance_value;


void mcs_tim_init(void);
void delay_mcs(uint32_t mcs);


void spi_2_init(uint8_t resistance_value);

#endif /* __SPI_2_INIT_H */