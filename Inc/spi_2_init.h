#ifndef __SPI_2_INIT_H
#define __SPI_2_INIT_H

#include "gpio.h"

extern uint8_t resistance_value;

void spi_2_init(uint8_t resistance_value);
void gain_change(uint8_t resistance_value);

#endif /* __SPI_2_INIT_H */