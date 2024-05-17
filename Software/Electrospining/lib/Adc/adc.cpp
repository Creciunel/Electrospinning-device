#include "adc.h"


void voltageMasureTask(void *pvParameters)
{
    // setup
    (void)pvParameters;

    // Create semaphore
    ADC_Semaphore = xSemaphoreCreateBinary();

    // Set ADC pin as input
    pinMode(ADC_PIN, INPUT);

    // loop
    for (;;)
    {
        // Wait for the semaphore
        if (xSemaphoreTake(ADC_Semaphore, portMAX_DELAY) == pdTRUE)
        {
            // Read ADC value
            adcValue = analogRead(ADC_PIN);

            // Release the semaphore
            xSemaphoreGive(ADC_Semaphore);

            // Print ADC value to Serial Monitor
            // Serial.println("ADC value: " + String(adcValue));
        }
        // Delay before next ADC reading
        vTaskDelay(pdMS_TO_TICKS(1000));
    }
}

/**
 * get ADC value
 * @return Voltage value
 * @note ADC_RESOLUTION * xSemaphoreGive(ADC_Semaphore) - voltage from 10K ohms resistor
 * (ADC_RESOLUTION * xSemaphoreGive(ADC_Semaphore)) * VOLTAGE_GAIN - Output voltage
 * @note Voltage value is not less than 0 and not more than 30000
 * @note ADC value is not less than 0 and not more than 1023
 * @note Voltage value = (ADC_RESOLUTION * ADC value) * VOLTAGE_GAIN
*/
int voltageValue(void){
    // ADC_RESOLUTION * xSemaphoreGive(ADC_Semaphore) - voltage from 10K ohms resistor
    // (ADC_RESOLUTION * xSemaphoreGive(ADC_Semaphore)) * VOLTAGE_GAIN - Output voltage
    return (ADC_RESOLUTION * adcValue) * VOLTAGE_GAIN;
}