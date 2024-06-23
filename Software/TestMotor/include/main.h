#include <Wire.h> 
#include <LiquidCrystal_I2C.h>

#include <Arduino.h>
#include <AFMotor.h>
#include <GyverEncoder.h>

#define ADDRESS 0x27 // I2C address

// Stepper motor constants
#define STEPPERNR 2
#define STEPS 200


// ADC constants
#define ADC_PIN A8 // ADC pin
#define ADC_RESOLUTION 5.0 / 1024.0
#define VOLTAGE_GAIN 20000

// Time constants
#define PRINT_DELAY 2000
#define COMMUNICATION_DELAY 100
#define ENCODER_DELAY 100

// Helper functions
#define MillisecondsToMinutes(milliseconds) ((milliseconds) / 60000.0)

// Encoder constants
#define  CLK 26
#define  DT  24
#define  SW  22