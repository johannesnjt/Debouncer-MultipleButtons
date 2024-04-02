#ifndef DEBOUNCER_H
#define DEBOUNCER_H

#include <stdint.h>

// Global constants
#define MAX_DEBOUNCER_PINS 8    // max amount of pins that's allowed
#define MAX_ARDUINO_PIN 57      // max amount of pins in Teensy 3.5
#define DEBOUNCER_STABLE_REPS 5 // the amount of consecutive values to find stability

// Debouncer state
#define DEBOUNCER_STATE_HIGH 1
#define DEBOUNCER_STATE_LOW 0
#define DEBOUNCER_STATE_RISING 2
#define DEBOUNCER_STATE_FALLING 3

// Error codes
#define DEBOUNCER_ERROR_OK 200                // there's no error
#define DEBOUNCER_ERROR_INVALID_PIN_ARRAY 201 // the array of pins can't be NULL
#define DEBOUNCER_ERROR_TOO_MANY_BUTTONS 202  // the array of pins can't be bigger than MAX_DEBOUNCER_PINS
#define DEBOUNCER_ERROR_PINS_REPEATED 203     // the array of pins can't have duplicated values
#define DEBOUNCER_ERROR_PIN_OUT_OF_RANGE 204  // the pins can't be bigger than MAX_ARDUINO_PIN
#define DEBOUNCER_ERROR_NOT_INITIALIZED 205   // when the driver is not initialized, debouncer_init should be called successfully before attempting anything else

/**
 * @brief Initialize the debouncer.
 * @param pins Pins in an array created for the debouncer.
 * @param pin_count Amount of pins in the array.
 * @return uint8_t The error codes.
 */
uint8_t debouncer_init(uint8_t *pins, uint8_t pin_count);

/**
 * @brief Update the state of every pin that's attached to the debouncer.
 */
void debouncer_update(void);

/**
 * @brief Get the state of a specific pin that's attached to the debouncer.
 *
 * @param pin The pin
 * @return uint8_t The state of the pin or the error codes
 */
uint8_t debouncer_get_button_state(uint8_t pin);
#endif