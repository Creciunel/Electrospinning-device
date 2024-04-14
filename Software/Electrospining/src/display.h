/**
 * Display function
 * 
 * @url https://github.com/prenticedavid/ILI9341_kbv.git
 * 
 * @url https://projecthub.arduino.cc/roger_marin/tutorial-for-ili9341-tft-lcd-sd-and-arduino-mega-part-4-00cb1b
 * 
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

// #define LCD_CS       A3 // Chip Select goes to Analog 3
// #define LCD_CD       A2 // Command/Data goes to Analog 2
// #define LCD_WR       A1 // LCD Write goes to Analog 1
// #define LCD_RD       A0 // LCD Read goes to Analog 0
// #define LCD_RESET    A4 // Can alternately just connect to Arduino's reset pin

#define CD_PIN          48 //DC
#define CS_PIN          53
#define RESET_PIN       49
#define SD_PIN          47 //sd-cs
#define MOSI_PIN        51
#define SCK_PIN         52

#define T_CS            44
#define T_CLK           52
#define T_DOUT          50
#define T_DIN           51
#define T_IRQ           46

extern uint8_t status;

extern void displayTask(void *pvParameters);

#endif