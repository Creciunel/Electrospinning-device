#include <Arduino.h>

#include <stdint.h>
// #include <AFMotor.h>

#define STEPPERNR 2
#define STEPS 200
#define MOTORDELAY 100 // 0.1 seconds

#define ADC_PIN 3   // ADC pin
#define ADCDELAY 100 // 0.1 seconds
#define ADC_RESOLUTION 5.0 / 1024.0
#define VOLTAGE_GAIN 20000

#define PRINT_DELAY 1000
#define COMMUNICATION_DELAY 100

#define SECONDS_TO_MINUTES(seconds) ((seconds) / 60.0)

uint16_t motorSpeed = 10;
uint32_t startTime = 100;
uint32_t runTime = 5000;

uint16_t adcValue;

uint32_t curMotorTime = 0;
uint32_t curAdcTime = 0;
uint32_t curPrintTime = 0;
uint32_t curCommunicationTime = 0;

uint8_t status = 1;

// AF_Stepper motor(STEPS, STEPPERNR); // uint16_t steps - revolution per steps, uint8_t num - stepper num connectet to sheeld
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

  // motor.setSpeed(motorSpeed); // is good 10 rpm

  curPrintTime = millis();
  curAdcTime = millis();
  curMotorTime = millis();
  curCommunicationTime = millis();
}

void loop()
{
  if (flag.start)
  {
    if (millis() - curMotorTime > MOTORDELAY)
    {

      uint16_t stepsNr = runTime * motorSpeed;
      //  steps, dir, style
      // motor.step(stepsNr, FORWARD, SINGLE);

      curMotorTime = millis();
    }
  }

  if (millis() - curAdcTime > ADCDELAY)
  {
    adcValue = analogRead(ADC_PIN);
    curAdcTime = millis();
  }

  // send
  if (millis() - curPrintTime > PRINT_DELAY)
  {
    // status, start/stop, voltage, speed, total time, runing time
    Serial.println(status + "," + String(flag.start) + "," + String(voltageValue(adcValue)) + "," + motorSpeed + "," + String(SECONDS_TO_MINUTES(startTime)) + "," + String(SECONDS_TO_MINUTES(millis() / 60000) - SECONDS_TO_MINUTES(startTime)));

    curPrintTime = millis();
  }

  //  read command
  if (millis() - curCommunicationTime > COMMUNICATION_DELAY)
  {
    if (Serial.available() > true)
    {
      char key = Serial.read();
      int val = Serial.parseInt();
      switch (key)
      {
      case 'm':
        motorSpeed = val; // rot/min
        // Serial.println("1, motorSpeed: " + String(motorSpeed) + " rpm");
        break;
      case 's':
        flag.start = val;

        // Serial.println("1, start: " + String(flag.start) + " val: " + String(val));
        if (flag.start)
          // get time in minutes
          startTime = millis(); // get start time
        break;
      case 't':
        // transgorm from min in ms
        runTime = val * 60 * 1000;
        // Serial.println("1, runTime: " + String(runTime / 60 / 1000) + " min");
        break;
      default:
        flag.status = 0;
        // Serial.println("-2, Wrong message! key: " + String(key) + ", val: " + String(val));
        break;
      }
    }
  }
}