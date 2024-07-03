#include <Wire.h> 
#include <LiquidCrystal_I2C.h>

#include <Arduino.h>
#include <AFMotor.h>
#include <GyverEncoder.h>

// #include <Stepper.h>

#define ADDRESS 0x27 // I2C address

// Stepper motor constants
#define STEPPERNR 1
#define STEPS 200
#define COIL_A 8
#define COIL_B 9
#define COIL_C 10
#define COIL_D 11

// #define FORWARD 1
// #define BACKWARD 0


// ADC constants
#define ADC_PIN A8 // ADC pin
#define ADC_RESOLUTION 5.0 / 1024.0
#define R2 10151.5 // 10k
#define R1 96840000 // 100k
// Calculate voltage gain between 2 resistors
#define VOLTAGE_GAIN ((R1 + R2) / R2)

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

// Relay constants
#define  RELAY 30
#define  RELAY1 32