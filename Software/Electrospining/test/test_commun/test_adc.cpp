// include unit test library and adc library
#include <unity.h>
#include "adc.h"

// init variables
uint16_t adcValue;

// setup function
void setUp(void)
{
}

// teardown function
void tearDown(void)
{
}

// test if value is not less than 0 after ADC function
// check if ADC function is not less than 0
// check if voltage value is not less than 0
void test_voltage_value_is_not_less_than_0(void)
{
    // Check if voltage value is not less than 0
    TEST_ASSERT_GREATER_THAN(0, voltageValue());
}

// test if voltage from ADC is not bigger than 30000V
// check if ADC value is not bigger than 30000V
void test_voltage_value_is_not_greater_than_30000(void)
{
    // Check if ADC value is not more than 30000
    TEST_ASSERT_LESS_THAN(30000, voltageValue());
}

// run unit tests in test mode
void run_tests(void)
{
    UNITY_BEGIN();
    RUN_TEST(test_voltage_value_is_not_less_than_0);
    RUN_TEST(test_voltage_value_is_not_greater_than_30000);
    UNITY_END();
}

#ifdef ARDUINO

#include <Arduino.h>

void setup()
{
    // NOTE!!! Wait for >2 secs
    // if board doesn't support software reset via Serial.DTR/RTS
    delay(2000);

    // set pin as input
    pinMode(ADC_PIN, INPUT);

    run_tests();
}

void loop()
{
    // blink LED
    digitalWrite(LED_BUILTIN, HIGH);
    delay(1000);
    digitalWrite(LED_BUILTIN, LOW);
    delay(1000);
}

#else

// run test
int main(int argc, char **argv)
{
    run_tests();
    return 0;
}

#endif
