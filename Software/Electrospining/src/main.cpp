/**
 * Main file wher is all the function declared
 *
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

uint16_t motorSpeed = 0; // rpm
uint16_t stepsNr = 100;

struct Flag
{
  uint8_t start;
} flag;

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
    // messages  format:status, stop/start, voltage, speed, time.
    xSemaphoreGive(ADC_Semaphore);

    Serial.println(status + "," + String(voltageValue()) + "," + motorSpeed + ",0,0");
  }

  if (Serial.available() > true)
  {
    char key = Serial.read();
    int val = Serial.parseInt();
    switch (key)
    {
    case 'm':
      motorSpeed = val;
      break;
    case 'n':
      stepsNr = val;
      break;
    case 's':
      flag.start = val;
      break;
    default:
      status = 0;
      Serial.println("-2, Wrong message! key: " + String(key) + ", val: " + String(val));
      break;
    }
  }

  vTaskDelay(pdMS_TO_TICKS(1000));
}