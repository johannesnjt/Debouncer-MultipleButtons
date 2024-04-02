#include "debouncer.h"
#include "bsp.h"

bool initialized = false;
uint8_t btn_pins[MAX_DEBOUNCER_PINS] = {0};
uint8_t btn_state[MAX_DEBOUNCER_PINS] = {0};
uint8_t btn_counter[MAX_DEBOUNCER_PINS] = {0};
uint8_t btn_count = 0;

bool isduplicated(uint8_t *arr, uint8_t size)
{
    bool found = false;
    // Searches for duplicate element
    for (int i = 0; i < size; i++)
    {
        for (int j = i + 1; j < size; j++)
        {
            if (arr[i] == arr[j])
            {
                found = true;
                break;
            }
        }
    }

    return found;
}

uint8_t debouncer_init(uint8_t *pins, uint8_t pin_count)
{
    uint8_t result = 0;
    initialized = false;

    if (pins == NULL)
    {
        result = DEBOUNCER_ERROR_INVALID_PIN_ARRAY;
    }
    else if (pin_count > MAX_DEBOUNCER_PINS)
    {
        result = DEBOUNCER_ERROR_TOO_MANY_BUTTONS;
    }
    else if (isduplicated(pins, pin_count))
    {
        result = DEBOUNCER_ERROR_PINS_REPEATED;
    }
    else
    {
        for (uint8_t i = 0; i < pin_count; i++)
        {
            btn_pins[i] = pins[i];
            btn_state[i] = DEBOUNCER_STATE_HIGH;
            btn_counter[i] = 0;
        }

        initialized = true;
        result = DEBOUNCER_ERROR_OK;
        btn_count = pin_count;
    }

    return result;
}

static void debouncer_update_button(uint8_t index)
{
    // Edges to flat

    if (btn_state[index] == DEBOUNCER_STATE_FALLING)
    {
        btn_state[index] = DEBOUNCER_STATE_LOW;
    }
    else if (btn_state[index] == DEBOUNCER_STATE_RISING)
    {
        btn_state[index] = DEBOUNCER_STATE_HIGH;
    }

    uint8_t pin = btn_pins[index];
    uint8_t pin_state = bsp_digital_read(pin);

    // Flat to edges

    if (pin_state == btn_state[index])
    {
        btn_counter[index] = 0;
    }
    else
    {
        btn_counter[index]++;

        if (btn_counter[index] == DEBOUNCER_STABLE_REPS)
        {
            btn_counter[index] = 0;

            if (btn_state[index] == DEBOUNCER_STATE_HIGH)
            {
                btn_state[index] = DEBOUNCER_STATE_FALLING;
            }
            else
            {
                btn_state[index] = DEBOUNCER_STATE_RISING;
            }
        }
    }
}

void debouncer_update(void)
{
    for (int i = 0; i < btn_count; i++)
    {
        debouncer_update_button(i);
    }
}

uint8_t debouncer_get_button_state(uint8_t pin)
{
    uint8_t result = 0;

    if (!initialized)
    {
        result = DEBOUNCER_ERROR_NOT_INITIALIZED;
    }
    else
    {
        for (int i = 0; i < btn_count; i++)
        {
            if (pin == btn_pins[i])
            {
                result = btn_state[i];
                break;
            }
        }
    }

    return result;
}