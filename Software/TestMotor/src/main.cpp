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

#define PRINT_DELAY 5000
#define COMMUNICATION_DELAY 100

#define MillisecondsToMinutes(milliseconds) ((milliseconds) / 60000.0) // SECONDS_TO_MINUTES(seconds) ((seconds) / 60.0)

uint16_t motorSpeed = 1000;
uint32_t startTime = 100;
uint32_t runTime = 10;

uint32_t curMotorTime = 0;
uint32_t curPrintTime = 0;
uint32_t startMomentTime = 0;

AF_Stepper motor(STEPS, STEPPERNR); // uint16_t steps - revolution per steps, uint8_t num - stepper num connectet to sheeld
struct Flag
{
  uint8_t status = 1;
  uint8_t start = 0;
} flag;

int voltageValue(uint16_t adcValue)
{
  // ADC_RESOLUTION * xSemaphoreGive(ADC_Semaphore) - voltage from 10K ohms resistor
  // (ADC_RESOLUTION * xSemaphoreGive(ADC_Semaphore)) * VOLTAGE_GAIN - Output voltage
  return (ADC_RESOLUTION * adcValue) * VOLTAGE_GAIN;
}

void setup()
{
  Serial.begin(115200);
  // print initial menu
  delay(20);
  Serial.println("m- motor speed, t- time for runing, s-start");

  curPrintTime = millis();
  curMotorTime = millis();
  startMomentTime = millis();

  motor.setSpeed(motorSpeed);
}

void loop()
{
  // if (flag.start)
  // {
  if (millis() - curMotorTime >= MOTORDELAY)
  {
    uint16_t stepsNr = runTime * motorSpeed;
    // steps, dir, style
    motor.step(stepsNr, FORWARD, SINGLE);

    curMotorTime = millis();
  }
  // }

  // send
  if (millis() - curPrintTime > PRINT_DELAY)
  {
    // status, start/stop, voltage, speed, total time, running time
    Serial.println(String(flag.status) + "," + String(flag.start) + "," + String(voltageValue(analogRead(ADC_PIN))) + "," + String(motorSpeed) + "," + String(MillisecondsToMinutes(millis()) - MillisecondsToMinutes(startMomentTime)) + "," + String(MillisecondsToMinutes(millis()) - MillisecondsToMinutes(startTime)));

    curPrintTime = millis();
  }

  // read command
  // if (millis() - curCommunicationTime > COMMUNICATION_DELAY)
  // {
  // if (Serial.available() > 0)
  // {
  //   char key = Serial.read();
  //   int val = Serial.parseInt();
  //   switch (key)
  //   {
  //   case 'm':
  //     motorSpeed = val; // rot/min
  //     motor.setSpeed(motorSpeed);
  //     break;
  //   case 's':
  //     flag.start = val;
  //     if (flag.start)
  //     {
  //       // start
  //       startTime = millis(); // get start time
  //       motor.setSpeed(motorSpeed);
  //     }else
  //     {
  //       // stop
  //       motor.release();
  //       motor.setSpeed(0);
  //       motor.step(0, FORWARD, SINGLE);
  //       // print stop motor
  //       Serial.println("0,0,0,0,0,0");
  //     }
  //     break;
  //   case 't':
  //     // transform from min in ms
  //     runTime = val * 60 * 1000;
  //     break;
  //   default:
  //     // flag.status = -2;
  //     Serial.println("-2, Wrong message! key: " + String(key) + ", val: " + String(val));
  //     break;
  //   }
  // }
}
