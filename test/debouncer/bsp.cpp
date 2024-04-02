#include "bsp.h"

static uint8_t fake_val = LOW;

void bsp_pin_mode(uint8_t pin, uint8_t mode)
{
    (void)pin;
    (void)mode;
}

uint8_t bsp_digital_read(uint8_t pin)
{
    return fake_val;
}

void bsp_fake_value(uint8_t pin, uint8_t val)
{
    fake_val = val;
}