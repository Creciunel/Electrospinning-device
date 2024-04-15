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

#include <AFMotor.h>

// Connect a stepper motor with 48 steps per revolution (7.5 degree)
// to motor port #2 (M3 and M4)
AF_Stepper motor(48, 2);

extern void motorsTask(void *pvParameters);

#endif