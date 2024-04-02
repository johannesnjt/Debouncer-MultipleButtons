#ifndef DEVENV
#endif

#include <unity.h>
#include "bsp.h"
#include "debouncer.h"

#define BUTTON_1_PIN 33
#define BUTTON_2_PIN 34

static bool everything_fine = false;
void setUp()
{
}
void tearDown()
{
}

void test_initialization(void)
{
    // Without initialization, everything will return DEBOUNCER_ERROR_NOT_INITIALIZED
    TEST_ASSERT_EQUAL_UINT8(DEBOUNCER_ERROR_NOT_INITIALIZED, debouncer_get_button_state(0));

    TEST_ASSERT_EQUAL_UINT8(DEBOUNCER_ERROR_INVALID_PIN_ARRAY, debouncer_init(NULL, 0));

    uint8_t too_many_pins[] = {0, 1, 2, 3, 4, 5, 6, 7, 8};
    TEST_ASSERT_EQUAL_UINT8(DEBOUNCER_ERROR_TOO_MANY_BUTTONS, debouncer_init(too_many_pins, sizeof(too_many_pins)));

    uint8_t pins_repeated[] = {0, 1, 2, 3, 4, 4, 6, 7};
    TEST_ASSERT_EQUAL_UINT8(DEBOUNCER_ERROR_PINS_REPEATED, debouncer_init(pins_repeated, sizeof(pins_repeated)));

    uint8_t pins[MAX_DEBOUNCER_PINS] = {0, 1, 2, 3, 4, 5, 6, 7};
    TEST_ASSERT_EQUAL_UINT8(DEBOUNCER_ERROR_OK, debouncer_init(pins, MAX_DEBOUNCER_PINS));

    TEST_ASSERT_EQUAL_UINT8(DEBOUNCER_STATE_HIGH, debouncer_get_button_state(pins[1]));
}

void test_state(void)
{
    uint8_t state1 = 0;

    uint8_t pins[BUTTON_1_PIN] = {0, 1, 2, 3, BUTTON_1_PIN, 5, 6, 7};
    TEST_ASSERT_EQUAL_UINT8(DEBOUNCER_ERROR_OK, debouncer_init(pins, MAX_DEBOUNCER_PINS));

    bsp_fake_value(BUTTON_1_PIN, LOW);

    debouncer_update();
    TEST_ASSERT_EQUAL_UINT8(DEBOUNCER_STATE_HIGH, debouncer_get_button_state(BUTTON_1_PIN));
    debouncer_update();
    TEST_ASSERT_EQUAL_UINT8(DEBOUNCER_STATE_HIGH, debouncer_get_button_state(BUTTON_1_PIN));
    debouncer_update();
    TEST_ASSERT_EQUAL_UINT8(DEBOUNCER_STATE_HIGH, debouncer_get_button_state(BUTTON_1_PIN));
    debouncer_update();
    TEST_ASSERT_EQUAL_UINT8(DEBOUNCER_STATE_HIGH, debouncer_get_button_state(BUTTON_1_PIN));
    debouncer_update();
    TEST_ASSERT_EQUAL_UINT8(DEBOUNCER_STATE_FALLING, debouncer_get_button_state(BUTTON_1_PIN));
    debouncer_update();
    TEST_ASSERT_EQUAL_UINT8(DEBOUNCER_STATE_LOW, debouncer_get_button_state(BUTTON_1_PIN));
    debouncer_update();
    TEST_ASSERT_EQUAL_UINT8(DEBOUNCER_STATE_LOW, debouncer_get_button_state(BUTTON_1_PIN));
    debouncer_update();
    TEST_ASSERT_EQUAL_UINT8(DEBOUNCER_STATE_LOW, debouncer_get_button_state(BUTTON_1_PIN));

    bsp_fake_value(BUTTON_1_PIN, HIGH);
    debouncer_update();
    TEST_ASSERT_EQUAL_UINT8(DEBOUNCER_STATE_LOW, debouncer_get_button_state(BUTTON_1_PIN));
    debouncer_update();
    TEST_ASSERT_EQUAL_UINT8(DEBOUNCER_STATE_LOW, debouncer_get_button_state(BUTTON_1_PIN));
    debouncer_update();
    TEST_ASSERT_EQUAL_UINT8(DEBOUNCER_STATE_LOW, debouncer_get_button_state(BUTTON_1_PIN));
    debouncer_update();
    TEST_ASSERT_EQUAL_UINT8(DEBOUNCER_STATE_LOW, debouncer_get_button_state(BUTTON_1_PIN));
    debouncer_update();
    TEST_ASSERT_EQUAL_UINT8(DEBOUNCER_STATE_RISING, debouncer_get_button_state(BUTTON_1_PIN));
    debouncer_update();
    TEST_ASSERT_EQUAL_UINT8(DEBOUNCER_STATE_HIGH, debouncer_get_button_state(BUTTON_1_PIN));
    debouncer_update();
    TEST_ASSERT_EQUAL_UINT8(DEBOUNCER_STATE_HIGH, debouncer_get_button_state(BUTTON_1_PIN));
    debouncer_update();
    TEST_ASSERT_EQUAL_UINT8(DEBOUNCER_STATE_HIGH, debouncer_get_button_state(BUTTON_1_PIN));
}

void loop()
{
}

#ifdef DEVENV
int main(void)
#else
void setup(void)
#endif
{
    UNITY_BEGIN();
    RUN_TEST(test_initialization);
    RUN_TEST(test_state);

#ifdef DEVENV
    return UNITY_END();
#else
    UNITY_END();
    return;
#endif
}
