#include <Arduino.h>
#include "debouncer.h"

static bool everything_is_fine = false;

#define BUTTON_PIN_1 33
#define BUTTON_PIN_2 34

void setup() 
{
    Serial.begin(9600);
    delay(2000);

    uint8_t pins[] = {BUTTON_PIN_1, BUTTON_PIN_2};
    if(debouncer_init(pins, sizeof(pins)) == DEBOUNCER_ERROR_OK) 
    {
        everything_is_fine = true;
    } 
}

void loop() 
{
    if(everything_is_fine)
    {
      static uint8_t prev_state = HIGH;
      debouncer_update();
      uint8_t state = debouncer_get_button_state(BUTTON_PIN_1);
      if(state != prev_state)
      {
          prev_state = state;
          Serial.printf("State Button 1: %d", state);
      }
    }
}