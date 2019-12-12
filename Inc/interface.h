#ifndef __INTERFACE_H
#define __INTERFACE_H

#include "gpio.h"
#include "usart.h"
#include "stdint.h"

extern uint8_t uart_buffer[9];

void send_message(uint16_t x, uint16_t y, uint16_t z, uint16_t p);

#endif /* __INTERFACE_H */