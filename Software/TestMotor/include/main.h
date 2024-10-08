#include <Wire.h>
#include <LiquidCrystal_I2C.h>
#include <Arduino.h>
#include <GyverEncoder.h>

#include <Arduino_FreeRTOS.h>

#define ADDRESS           0x27 // I2C address
#define SCL_PIN          21
#define SDA_PIN          20

// Definește pinii pentru TB6600
#define DIR_PIN          44   // DIR+
#define PUL_PIN          46   // PUL+
#define ENA_PIN          48   // ENA+

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
#define CLK              26
#define DT                24
#define SW                22

// Relay constants
#define RELAY             30
#define RELAY1            32

#define PWM_PIN          13 

int voltageValue(uint16_t adcValue)
{
  return (ADC_RESOLUTION * adcValue) * VOLTAGE_GAIN;
}

void checkEncoder();