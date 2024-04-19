/**
 * get ADC value
 */
// #pragma once

#ifndef ADC_H
#define ADC_H

#include <Arduino.h>
#include <Arduino_FreeRTOS.h>
#include <semphr.h>
#include "task.h"

// Pin to masure output voltage
#define ADC_PIN         A8 // 62

#define ADC_RESOLUTION  5.0 / 1024.0
#define VOLTAGE_GAIN    20000

// Semaphore handle
extern SemaphoreHandle_t ADC_Semaphore;

extern uint16_t adcValue;
extern uint8_t status;

// Prototipul funcției task-ului voltageMasureTask
extern void voltageMasureTask(void *pvParameters);
int voltageValue(void);

#endif