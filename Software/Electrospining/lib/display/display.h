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

// These are the four touchscreen analog pins
#define YP A2 // must be an analog pin, use "An" notation!
#define XM A3 // must be an analog pin, use "An" notation!
#define YM 8  // can be any digital pin
#define XP 9  // can be any digital pin

// This is calibration data for the raw touch data to the screen coordinates
#define TS_MINX 150
#define TS_MINY 120
#define TS_MAXX 920
#define TS_MAXY 940

#define MINPRESSURE 10
#define MAXPRESSURE 1000

// The display uses hardware SPI, plus #9 & #10
#define TFT_CS 10
#define TFT_DC 9

// Size of the color selection boxes and the paintbrush size
#define BOXSIZE 40
#define PENRADIUS 3

extern uint8_t status;

extern void displayTask(void *pvParameters);

#endif