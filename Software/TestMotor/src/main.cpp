#include "main.h"

void vTaskEncoder(void *pvParameters);
void vTaskMotor(void *pvParameters);
void vTaskLCD(void *pvParameters);
void vTaskCommunication(void *pvParameters);
void vTaskTransformer(void *pvParameters);

// Motor constants
uint16_t motorSpeed = 1;
uint16_t motorDelay = 1000 / motorSpeed;
uint8_t motorDirection = LOW;

// Transformer variables
uint8_t pwmValue = 0;

// Encoder și LCD
Encoder enc(CLK, DT, SW, TYPE1);
LiquidCrystal_I2C lcd(ADDRESS, 16, 2);

struct Flag
{
  uint8_t start = 0;
} flag;

void setup()
{
  // Crearea sarcinilor
  xTaskCreate(vTaskEncoder, "Encoder Task", 128, NULL, 2, NULL);
  xTaskCreate(vTaskMotor, "Motor Task", 128, NULL, 1, NULL);
  xTaskCreate(vTaskLCD, "LCD Task", 128, NULL, 1, NULL);
  xTaskCreate(vTaskCommunication, "Communication Task", 128, NULL, 1, NULL);
  xTaskCreate(vTaskTransformer, "Transformer Task", 128, NULL, 1, NULL);

  // Pornește scheduler-ul FreeRTOS
  vTaskStartScheduler();

// Initializarea LCD
  lcd.init(); // Asigură-te că LCD-ul este inițializat
  lcd.backlight(); // Activează iluminarea de fundal

  // initializarea seriala
  Serial.begin(115200);
}

void loop() {}

void vTaskEncoder(void *pvParameters)
{
  pinMode(SW, INPUT_PULLUP);
  pinMode(CLK, INPUT_PULLUP);
  pinMode(DT, INPUT_PULLUP);

  for (;;)
  {
    enc.tick(); // Actualizează starea encoderului

    checkEncoder();

    vTaskDelay(100 / portTICK_PERIOD_MS); // Întârziere mai mică pentru reacții rapide
  }
}

void vTaskMotor(void *pvParameters)
{
  pinMode(DIR_PIN, OUTPUT);
  pinMode(PUL_PIN, OUTPUT);
  pinMode(ENA_PIN, OUTPUT);

  digitalWrite(ENA_PIN, LOW);
  digitalWrite(DIR_PIN, HIGH);

  for (;;)
  {
    if (flag.start)
    {
      digitalWrite(PUL_PIN, HIGH);
      delayMicroseconds(100);
      digitalWrite(PUL_PIN, LOW);
      delayMicroseconds(100);
    }
    vTaskDelay(10 / portTICK_PERIOD_MS); // Delay mai mic pentru reacții rapide
  }
}

void vTaskLCD(void *pvParameters)
{
  
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

  for (;;)
  {
    lcd.setCursor(0, 0);
    lcd.print("V:" + String(int(voltageValue(analogRead(ADC_PIN)) / 1000.0)));

    vTaskDelay(1000 / portTICK_PERIOD_MS); // Actualizează LCD-ul la fiecare secundă
  }
}

void vTaskTransformer(void *pvParameters)
{
  // init transformer pin
  pinMode(PWM_PIN, OUTPUT);

  // Setare Timer0 pentru a obține o frecvență de aproximativ 15.625 kHz
  TCCR0A = (1 << WGM00) | (1 << WGM01);
  TCCR0B = (1 << CS01);

  for (;;)
  {
    analogWrite(PWM_PIN, pwmValue);
    vTaskDelay(1000 / portTICK_PERIOD_MS);
  }
}

void vTaskCommunication(void *pvParameters)
{
  Serial.println("System Initialized\r\n");
  Serial.println("Available commands:\r\n");
  Serial.println("m <value> - Set motor speed (steps per second)\r\n");
  Serial.println("s <0/1> - Stop/Start motor\r\n");
  Serial.println("d <0/1> - Set motor direction (0 = BACKWARD, 1 = FORWARD)\r\n");
  Serial.println("p <0/255> - Set PWM value for Transformer\r\n");

  for (;;)
  {
    if (Serial.available() > 0)
    {
      char key = Serial.read();
      int val = Serial.parseInt();
      

      switch (key)
      {
      case 's':
        flag.start = val;
        digitalWrite(ENA_PIN, flag.start ? LOW : HIGH);
        break;
      case 'd':
        motorDirection = val ? HIGH : LOW;
        digitalWrite(DIR_PIN, motorDirection);
        break;
      case 'm':
        motorSpeed = val;
        motorDelay = max(1000 / motorSpeed, 1);
        break;
      case 'p':
        pwmValue = val;

        if (pwmValue > 255)
          pwmValue = 255;
        else if (pwmValue < 0)
          pwmValue = 0;

        Serial.println("command: p, value: " + String(pwmValue));
        break;
      default:
        Serial.println("Wrong command! key: " + String(key) + ", val: " + String(val));
        break;
      }
    }
    vTaskDelay(100 / portTICK_PERIOD_MS);
  }
}

void checkEncoder()
{
  static uint32_t lastCheckTime = 0;

  if (millis() - lastCheckTime >= ENCODER_DELAY)
  {
    lastCheckTime = millis();

    if (enc.isClick())
    {
      flag.start = !flag.start;
      digitalWrite(ENA_PIN, flag.start ? LOW : HIGH);
      lcd.setCursor(5, 1);
      lcd.print("s:" + String(flag.start));
      Serial.println("command: s, value: " + String(flag.start));
    }
    else if (enc.isDouble())
    {
      motorDirection = !motorDirection;
      digitalWrite(DIR_PIN, motorDirection);
      lcd.setCursor(0, 1);
      lcd.print(motorDirection ? "d:F" : "d:B");
      Serial.println("command: d, value: " + String(motorDirection));
    }
    else if (enc.isRight())
    {
      motorSpeed++;
      if (motorSpeed > 100)
        motorSpeed = 100;
      motorDelay = max(1000 / motorSpeed, 1);
      lcd.setCursor(5, 0);
      lcd.print("kV RPM:" + String(motorSpeed));
      Serial.println("command: m, value: " + String(motorSpeed));
    }
    else if (enc.isLeft())
    {
      motorSpeed--;
      if (motorSpeed < 1)
        motorSpeed = 1;
      motorDelay = max(1000 / motorSpeed, 1);
      lcd.setCursor(5, 0);
      lcd.print("kV RPM:" + String(motorSpeed));
      Serial.println("command: m, value: " + String(motorSpeed));
    }
  }
}