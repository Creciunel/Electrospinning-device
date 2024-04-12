/**
 * Display function
 */
// #pragma once

#ifndef DISPLAY_H
#define DISPLAY_H

#include <Arduino.h>
#include <Arduino_FreeRTOS.h>
#include <semphr.h>
#include "task.h"

#include <SPI.h>
#include <ILI9341_due_config.h>
#include <ILI9341_due.h>
#include "fonts/Arial_bold_14.h"
#include "fonts/roboto16.h"
#include "fonts/roboto32.h"
#include "fonts/roboto70nums.h"

// Pin to connect display https://www.hackster.io/roger_marin/tutorial-for-ili9341-tft-lcd-sd-and-arduino-mega-part-1-02f659
#define CD_PIN          48 //DC
#define CS_PIN          53
#define RESET_PIN       49
#define SD_PIN          47 //sd-cs
#define MOSI_PIN        51
#define SCK_PIN         52

extern uint8_t status;

extern void displayTask(void *pvParameters);

#endif