#include <Arduino.h>

#include <stdint.h>
#include <AFMotor.h>

#define STEPPERNR 2
#define STEPS 200
#define MOTORDELAY 100 // 0.1 seconds

#define ADC_PIN A8   // ADC pin
#define ADCDELAY 100 // 0.1 seconds
#define ADC_RESOLUTION 5.0 / 1024.0
#define VOLTAGE_GAIN 20000

#define PRINT_DELAY 1000

uint16_t motorSpeed = 10;
uint32_t startTime = 100;
uint32_t runTime = 5000;

uint16_t adcValue;

uint32_t curMotorTime = 0;
uint32_t curAdcTime = 0;
uint32_t curPrintTime = 0;

AF_Stepper motor(STEPS, STEPPERNR); // uint16_t steps - revolution per steps, uint8_t num - stepper num connectet to sheeld

int voltageValue(uint16_t adcValue)
{
  // ADC_RESOLUTION * xSemaphoreGive(ADC_Semaphore) - voltage from 10K ohms resistor
  // (ADC_RESOLUTION * xSemaphoreGive(ADC_Semaphore)) * VOLTAGE_GAIN - Output voltage
  return (ADC_RESOLUTION * adcValue) * VOLTAGE_GAIN;
}

void setup()
{
  Serial.begin(115200);

  motor.setSpeed(motorSpeed); // is good 10 rpm

  curPrintTime = millis();
  curAdcTime = millis();
  curMotorTime = millis();
}

void loop()
{

  if (millis() - curMotorTime > MOTORDELAY)
  {

    uint16_t stepsNr = runTime * motorSpeed;
    //  steps, dir, style
    motor.step(stepsNr, FORWARD, SINGLE);

    curMotorTime = millis();
  }

  if (millis() - curAdcTime > ADCDELAY)
  {
    adcValue = analogRead(ADC_PIN);
    curAdcTime = millis();
  }
  if (millis() - curPrintTime > PRINT_DELAY)
  {
    Serial.println("ADC value: " + String(adcValue) + " Voltage: " + String(voltageValue(adcValue)));

    curPrintTime = millis();
  }
}
