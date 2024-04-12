/**
 * motors driver L293D
 */
// #pragma once

#ifndef MOTOR_H
#define MOTOR_H

#include <Arduino.h>
#include <Arduino_FreeRTOS.h>
#include <semphr.h>
#include "task.h"


extern void motorsTask(void *pvParameters);

#endif