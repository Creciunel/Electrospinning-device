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

#define SECONDS_TO_MINUTES(seconds) ((seconds) / 60.0)

// void displayTask(void *pvParameters);
void voltageMasureTask(void *pvParameters);
void motorsTask(void *pvParameters);

// Semaphore handle
SemaphoreHandle_t ADC_Semaphore;

uint16_t adcValue;
uint8_t status = 1; // init without problems

uint32_t startTime; // seconds
uint32_t runTime;   // minutes

uint16_t motorSpeed = 0; // rpm

struct Flag flag;

void setup(void)
{
  pinMode(13, OUTPUT);
  digitalWrite(13, LOW);

  Serial.begin(115200);

  // xTaskCreate(displayTask, "Dysplay info", 1000, NULL, 1, NULL);
  xTaskCreate(voltageMasureTask, "Masure voltage", 1000, NULL, 1, NULL);
  xTaskCreate(motorsTask, "Connect motors", 1000, NULL, 1, NULL);

  vTaskStartScheduler();
}

void loop(void)
{

  TickType_t xTickCount;
  uint32_t ulTickCountSeconds;

  xTickCount = xTaskGetTickCount();

  // Convertim tick-urile în secunde
  ulTickCountSeconds = xTickCount / configTICK_RATE_HZ;

  // Main comunicate protocol
  if (status)
  {
    // messages  format:status, stop/start, voltage, speed, seted time, actual, runing time.
    xSemaphoreGive(ADC_Semaphore);

    Serial.println(status + "," + String(flag.start) + "," + String(voltageValue()) + "," + motorSpeed + "," + String(SECONDS_TO_MINUTES(ulTickCountSeconds)) + "," + String(SECONDS_TO_MINUTES(ulTickCountSeconds) - SECONDS_TO_MINUTES(startTime)));
  }

  // Check if seted time for work are already done
  if (SECONDS_TO_MINUTES(ulTickCountSeconds) - SECONDS_TO_MINUTES(startTime) >= runTime && flag.start)
  {
    flag.start = 0;
  }

  // Read command from Windows app
  if (Serial.available() > true)
  {
    char key = Serial.read();
    int val = Serial.parseInt();
    switch (key)
    {
    case 'm':
      motorSpeed = val; // rot/min
      break;
    case 's':
      flag.start = val;

      if (flag.start)
        startTime = ulTickCountSeconds; // get start time
      break;
    case 't':
      runTime = val; // min
      break;
    default:
      status = 0;
      Serial.println("-2, Wrong message! key: " + String(key) + ", val: " + String(val));
      break;
    }
  }

  digitalWrite(13, !digitalRead(13));
  vTaskDelay(pdMS_TO_TICKS(1000));
}