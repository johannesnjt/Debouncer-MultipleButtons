#ifndef BSP_H
#define BSP_H

#include <stdint.h>

void bsp_pin_mode(uint8_t pin, uint8_t mode);
uint8_t bsp_digital_read(uint8_t pin);

#endif