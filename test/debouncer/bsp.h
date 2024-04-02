#ifndef BSP_h
#define BSP_h

#include <stdint.h>

#define LOW 0
#define HIGH 1

void bsp_pin_mode(uint8_t pin, uint8_t mode);

uint8_t bsp_digital_read(uint8_t pin);

void bsp_fake_value(uint8_t pin, uint8_t val);

#endif