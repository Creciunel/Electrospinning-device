#include "main.h"

// Definește pinii pentru TB6600
#define DIR_PIN 2
#define STEP_PIN 3
#define ENABLE_PIN 4 // Dacă folosești pinul de activare

// Motor constants
uint16_t motorSpeed = 1; // Viteza motorului (pași pe secundă)
uint16_t motorDelay = 1000 / motorSpeed; // Întârzierea între pași în milisecunde
uint8_t motorDirection = LOW; // Direcția motorului (LOW sau HIGH)

// Time constants
uint32_t curMotorTime = 0;
uint32_t curPrintTime = 0;
uint32_t curCommunicationTime = 0;
uint32_t curEncoderTime = 0;

// Encoder și LCD
Encoder enc(CLK, DT, SW);
LiquidCrystal_I2C lcd(ADDRESS, 16, 2);

struct Flag
{
  uint8_t start = 0;
} flag;

int voltageValue(uint16_t adcValue)
{
  return (ADC_RESOLUTION * adcValue) * VOLTAGE_GAIN;
}

void setup()
{
  pinMode(DIR_PIN, OUTPUT);
  pinMode(STEP_PIN, OUTPUT);
  pinMode(ENABLE_PIN, OUTPUT);

  // Dezactivează motorul la început
  digitalWrite(ENABLE_PIN, LOW);

  Serial.begin(115200);
  delay(100);

  Serial.println("System Initialized\r\n");
  Serial.println("Available commands:\r\n");
  Serial.println("m <value> - Set motor speed (steps per second)\r\n");
  Serial.println("s <0/1> - Stop/Start motor\r\n");
  Serial.println("d <0/1> - Set motor direction (0 = BACKWARD, 1 = FORWARD)\r\n");

  curPrintTime = millis();
  curMotorTime = millis();
  curCommunicationTime = millis();
  curEncoderTime = millis();

  // Encoder type one step or 2
  enc.setType(TYPE1);

  // LCD
  lcd.init();
  lcd.backlight();
  lcd.setCursor(0, 0);
  lcd.print("V:" + String(int(voltageValue(analogRead(ADC_PIN)) / 1000.0)));
  lcd.setCursor(5, 0);
  lcd.print("kV RPM:" + String(motorSpeed));
  lcd.setCursor(0, 1);
  if (motorDirection == HIGH)
    lcd.print("d:F");
  else
    lcd.print("d:B");
  lcd.setCursor(5, 1);
  lcd.print("s:" + String(flag.start));
}

void loop()
{
  enc.tick();

  if (millis() - curEncoderTime >= ENCODER_DELAY)
  {
    curEncoderTime = millis();

    if (enc.isClick())
    {
      flag.start = !flag.start;
      digitalWrite(ENABLE_PIN, flag.start ? HIGH : LOW);
      Serial.println("Encoder click start, value: " + String(flag.start));
      lcd.setCursor(5, 1);
      lcd.print("s:" + String(flag.start));
    }
    else if (enc.isDouble())
    {
      motorDirection = !motorDirection;
      digitalWrite(DIR_PIN, motorDirection);
      Serial.println("Encoder click direction, value: " + String(motorDirection ? "FORWARD" : "BACKWARD"));
      lcd.setCursor(0, 1);
      lcd.print(motorDirection ? "d:F" : "d:B");
    }
    else if (enc.isRight())
    {
      motorSpeed++;
      if (motorSpeed > 100)
        motorSpeed = 100;
      motorDelay = 1000 / motorSpeed;
      Serial.println("Encoder click speed, value: " + String(motorSpeed));
      lcd.setCursor(5, 0);
      lcd.print("kV RPM:" + String(motorSpeed));
    }
    else if (enc.isLeft())
    {
      motorSpeed--;
      if (motorSpeed < 1)
        motorSpeed = 1;
      motorDelay = 1000 / motorSpeed;
      Serial.println("Encoder click speed, value: " + String(motorSpeed));
      lcd.setCursor(5, 0);
      lcd.print("kV RPM:" + String(motorSpeed));
    }
  }

  if (flag.start && millis() - curMotorTime >= motorDelay)
  {
    curMotorTime = millis();
    digitalWrite(STEP_PIN, HIGH);
    delayMicroseconds(100);
    digitalWrite(STEP_PIN, LOW);
    delayMicroseconds(100);
  }

  if (millis() - curPrintTime >= PRINT_DELAY)
  {
    curPrintTime = millis();

    Serial.print("Motor Speed: ");
    Serial.print(motorSpeed);
    Serial.println(" steps/sec");

    Serial.print("Voltage: ");
    Serial.println(voltageValue(analogRead(ADC_PIN)));
    lcd.setCursor(0, 0);
    lcd.print("V:" + String(int(voltageValue(analogRead(ADC_PIN)) / 1000.0)));
  }

  if (millis() - curCommunicationTime >= COMMUNICATION_DELAY)
  {
    curCommunicationTime = millis();

    if (Serial.available() > 0)
    {
      char key = Serial.read();
      int val = Serial.parseInt();

      switch (key)
      {
      case 's':
        flag.start = val;
        digitalWrite(ENABLE_PIN, flag.start ? HIGH : LOW);
        Serial.println("command: s, value: " + String(flag.start));
        break;
      case 'd':
        motorDirection = val ? HIGH : LOW;
        digitalWrite(DIR_PIN, motorDirection);
        Serial.println("command: d, value: " + String(motorDirection ? "FORWARD" : "BACKWARD"));
        break;
      case 'm':
        motorSpeed = val;
        motorDelay = 1000 / motorSpeed;
        Serial.println("command: m, value: " + String(motorSpeed));
        break;
      default:
        Serial.println("Wrong command! key: " + String(key) + ", val: " + String(val));
        break;
      }
    }
  }
}