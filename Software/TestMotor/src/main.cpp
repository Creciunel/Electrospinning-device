#include <Arduino.h>

#include <stdint.h>
#include <AFMotor.h>

#define STEPPERNR 2
#define STEPS 200

uint16_t motorSpeed = 10;
uint32_t startTime = 100;
uint32_t runTime = 5000;

AF_Stepper motor(STEPS, STEPPERNR); // uint16_t steps - revolution per steps, uint8_t num - stepper num connectet to sheeld

void setup()
{
  Serial.begin(115200);

  motor.setSpeed(motorSpeed); // is good 10 rpm
}

void loop()
{
  uint16_t stepsNr = runTime * motorSpeed;
  //  steps, dir, style
  motor.step(stepsNr, FORWARD, SINGLE);

  delay(20);
}
