#include "adc.h"

void voltageMasureTask(void *pvParameters)
{
    // setup
    (void)pvParameters;

    // Create semaphore
    ADC_Semaphore = xSemaphoreCreateBinary();

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

int voltageValue(void){
    // ADC_RESOLUTION * xSemaphoreGive(ADC_Semaphore) - voltage from 10K ohms resistor
    // (ADC_RESOLUTION * xSemaphoreGive(ADC_Semaphore)) * VOLTAGE_GAIN - Output voltage
    return (ADC_RESOLUTION * adcValue) * VOLTAGE_GAIN;
}