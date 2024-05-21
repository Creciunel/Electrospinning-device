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
#include <Wire.h>

#include <Adafruit_GFX.h> // Core graphics library
#include <SPI.h>
#include <Adafruit_ILI9341.h>
#include "TouchScreen.h"

// #include <Arduino_GFX_Library.h>
// #include <XPT2046_Touchscreen.h>

// #define TFT_BL 6
// #define TFT_RST 7
// #define TFT_MISO 12
// #define TFT_MOSI 11
// #define TFT_DC 8
// #define TFT_SCK 13
// #define TFT_CS 9

// #define TOUCH_SCK 13
// #define TOUCH_CS 14
// #define TOUCH_MOSI 15
// #define TOUCH_MISO 12
// #define TOUCH_INT 17


// These are the four touchscreen analog pins
#define YP A14 // must be an analog pin, use "An" notation!
#define XM A15 // must be an analog pin, use "An" notation!
#define YM 48  // can be any digital pin
#define XP 49  // can be any digital pin

// This is calibration data for the raw touch data to the screen coordinates
#define TS_MINX 150
#define TS_MINY 120
#define TS_MAXX 920
#define TS_MAXY 940

#define MINPRESSURE 10
#define MAXPRESSURE 1000

// The display uses hardware SPI, plus #9 & #10
#define TFT_CS      53
#define TFT_DC      46
#define TFT_MOSI    51
#define TFT_SCLK    52
#define TFT_RST     47

// Size of the color selection boxes and the paintbrush size
#define BOXSIZE 40
#define PENRADIUS 3

extern uint8_t status;

extern void displayTask(void *pvParameters);

#endif