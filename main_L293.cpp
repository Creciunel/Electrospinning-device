#include "main.h"

// Motor constants
uint16_t motorSpeed = 1;
uint16_t motorDelay = 5;           // 0.01 seconds
uint8_t motorDirection = BACKWARD; // Direcția motorului (FORWARD sau BACKWARD)

// Time constants
uint32_t curMotorTime = 0;
uint32_t curPrintTime = 0;
uint32_t curCommunicationTime = 0;
uint32_t curEncoderTime = 0;

AF_Stepper motor(STEPS, STEPPERNR); // uint16_t steps - revolution per steps, uint8_t num connected to shield

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
  // close relay
  digitalWrite(RELAY, LOW);
  Serial.begin(115200);
  delay(100); // Give time for Serial to initialize

  Serial.println("System Initialized\r\n");
  Serial.println("Available commands:\r\n");
  Serial.println("m <value> - Set motor speed (RPM)\r\n");
  Serial.println("s <0/1> - Stop/Start motor\r\n");
  Serial.println("d <0/1> - Set motor direction (0 = BACKWARD, 1 = FORWARD)\r\n");

  curPrintTime = millis();
  curMotorTime = millis();
  curCommunicationTime = millis();
  curEncoderTime = millis();

  // Encoder type one spet ore 2
  enc.setType(TYPE1);

  // LCD
  lcd.init();
  lcd.backlight(); // Включаем подсветку дисплея
  lcd.setCursor(0, 0);
  lcd.print("V:" + String(int(voltageValue(analogRead(ADC_PIN)) / 1000.0)));
  lcd.setCursor(5, 0);
  lcd.print("kV RPM:" + String(motorSpeed));
  lcd.setCursor(0, 1);
  if (motorDirection == FORWARD)
    lcd.print("d:F");
  else
    lcd.print("d:B");
  lcd.setCursor(5, 1);
  lcd.print("s:" + String(flag.start));
}

void loop()
{
  // encoder
  enc.tick();

  if (millis() - curEncoderTime >= ENCODER_DELAY)
  {
    curEncoderTime = millis();

    if (enc.isClick())
    {
      if (flag.start)
      {
        flag.start = 0;
        digitalWrite(RELAY, LOW);
      }

      else
        flag.start = 1;
      digitalWrite(RELAY, HIGH);

      Serial.println("Encoder cklick start, value: " + String(flag.start));
      lcd.setCursor(5, 1);
      lcd.print("s:" + String(flag.start));
    }
    else if (enc.isDouble())
    {
      if (motorDirection == FORWARD)
      {
        motorDirection = BACKWARD;
        Serial.println("Encoder cklick direction, value: BACKWARD ");

        lcd.setCursor(0, 1);
        lcd.print("d:B");
      }
      else
      {
        motorDirection = FORWARD;
        Serial.println("Encoder cklick direction, value: FORWARD ");

        lcd.setCursor(0, 1);
        lcd.print("d:F");
      }
    }
    else if (enc.isRight())
    {
      motorSpeed++;
      if (motorSpeed > 100)
        motorSpeed = 100;
      Serial.println("Encoder cklick speed, value: " + String(motorSpeed));
      lcd.setCursor(5, 0);
      lcd.print("kV RPM:" + String(motorSpeed));
    }
    else if (enc.isLeft())
    {
      motorSpeed--;
      if (motorSpeed == 0)
        motorSpeed = 1;
      Serial.println("Encoder cklick speed, value: " + String(motorSpeed));
      lcd.setCursor(5, 0);
      lcd.print("kV RPM:" + String(motorSpeed));
    }
  }

  // Example to rotate the motor in one direction with a specified speed
  if (flag.start)
  {
    // if (millis() - curMotorTime >= motorDelay)
    // {
    // curMotorTime = millis();

    // Set initial motor direction and speed
    motor.setSpeed(motorSpeed); // Set motor speed in RPM
    motor.release();            // Ensure motor is released at start

    motor.step(1, motorDirection, SINGLE);
    // }
  }

  if (millis() - curPrintTime >= PRINT_DELAY)
  {
    curPrintTime = millis();

    // print moror speed
    Serial.print("Motor Speed: ");
    Serial.print(motorSpeed);
    Serial.println(" RPM");

    // print voltage
    Serial.print("Voltage: ");
    Serial.println(voltageValue(analogRead(ADC_PIN)));
    lcd.setCursor(0, 0);
    lcd.print("V:" + String(int(voltageValue(analogRead(ADC_PIN)) / 1000.0)));
  }

  if (millis() - curCommunicationTime >= COMMUNICATION_DELAY)
  {
    curCommunicationTime = millis();

    // Read command from Windows app
    if (Serial.available() > true)
    {
      char key = Serial.read();
      int val = Serial.parseInt();

      switch (key)
      {
      case 's':
        flag.start = val;
        if (flag.start == 0)
        {
          digitalWrite(RELAY, LOW);
        }else{
          digitalWrite(RELAY, HIGH);
        }

        Serial.println("command: s, value: " + String(flag.start));
        break;
      case 'd':
        if (val == 0)
        {
          motorDirection = BACKWARD;
          Serial.println("command: d, value: BACKWARD ");
        }
        else
        {
          motorDirection = FORWARD;
          Serial.println("command: d, value: FORWARD ");
        }
        break;
      case 'm':
        motorSpeed = val;
        Serial.println("command: m, value: " + String(motorSpeed));
        break;

      default:
        // Comanda gresita
        Serial.println("Wrong command! key: " + String(key) + ", val: " + String(val));
        break;
      }
    }
  }
}