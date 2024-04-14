/**
 * motors driver L293D
 * 
 * @ulr https://www.instructables.com/Arduino-L293D-Motor-Driver-Shield-Tutorial/
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