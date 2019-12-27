#ifndef __MAIN_LOOP_H
#define __MAIN_LOOP_H

#include "stdbool.h"
#include "adc_controller.h"
#include "interface.h"
#include "spi_2_init.h"

extern uint16_t memory_buffer[4];               //буфер хранения данных с АЦП
extern _Bool flag;                              //флаг отправки

#endif /* __MAIN_LOOP_H */