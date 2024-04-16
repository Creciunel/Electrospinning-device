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

#include <stdint.h>
#include <AFMotor.h>

#define STEPPERNR   2
#define STEPS       48

extern struct Flag {
    uint8_t start;
} flag;

extern uint16_t motorSpeed;
extern uint32_t startTime;
extern uint32_t runTime;

extern void motorsTask(void *pvParameters);

#endif