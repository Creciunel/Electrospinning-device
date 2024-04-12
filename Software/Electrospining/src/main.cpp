/**
 * Main file wher is all the function declared
 *
 * */
#include <Arduino.h>
#include <Arduino_FreeRTOS.h>
#include <semphr.h>
#include "task.h"

#include "adc.h"
#include "display.h"
#include "motor.h"


void displayTask(void *pvParameters);
void voltageMasureTask(void *pvParameters);
void motorsTask(void *pvParameters);

// Semaphore handle
SemaphoreHandle_t ADC_Semaphore;

uint16_t adcValue;
uint8_t status;

void setup(void)
{
  Serial.begin(115200);

  xTaskCreate(displayTask, "Dysplay info", 1000, NULL, 1, NULL);
  xTaskCreate(voltageMasureTask, "Masure voltage", 1000, NULL, 1, NULL);
  xTaskCreate(motorsTask, "Connect motors", 1000, NULL, 1, NULL);

  vTaskStartScheduler();
}

void loop(void)
{
  // Main comunicate protocol
  if (status)
  {
    // messages  format:status, voltage, speed, time.
    xSemaphoreGive(ADC_Semaphore);
    
    Serial.println(status + String(voltageValue()) + ",0,0,0");
  }

  vTaskDelay(pdMS_TO_TICKS(1000));
}