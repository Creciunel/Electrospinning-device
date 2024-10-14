#include <Wire.h>
#include <LiquidCrystal_I2C.h>
#include <Arduino.h>

#include <Arduino_FreeRTOS.h>

#include <Adafruit_Sensor.h>
#include <Adafruit_BME280.h>

#include <mwc_stepper.h>
#include <GyverEncoder.h>

#define ADDRESS           0x27 // I2C address
#define SCL_PIN          21
#define SDA_PIN          20

// Definește pinii pentru TB6600
#define DIR_PIN          46    // DIR+
#define PUL_PIN          44    // PUL+
#define ENA_PIN          48   // ENA+

#define CLOCKWISE 1
#define COUNTERCLOCKWISE 0

#define PULSE 200

// ADC constants
#define ADC_PIN          A8 // ADC pin
#define ADC_RESOLUTION    5.0 / 1024.0
#define R2                10151.5 // R2 resistor value in ohms
#define R1                96840000 // R1 resistor value in ohms

// Calculate voltage gain between two resistors
#define VOLTAGE_GAIN ((R1 + R2) / R2)

// Time constants
#define PRINT_DELAY      2000
#define COMMUNICATION_DELAY   100
#define ENCODER_DELAY      100

// Helper functions
#define MillisecondsToMinutes(milliseconds) ((milliseconds) / 60000.0)

// Encoder constants
#define CLK               26
#define DT                24
#define SW                22

// Relay constants
#define RELAY             30
#define RELAY1            32

#define PWM_PIN          13 

// display state
enum MenuState {
    MAIN_MENU,
    SELECT_DIRECTION,
    SELECT_SPEED,
    SENSOR_VALUES
};

MenuState currentState = MAIN_MENU;

int voltageValue(uint16_t adcValue)
{
  return (ADC_RESOLUTION * adcValue) * VOLTAGE_GAIN;
}

