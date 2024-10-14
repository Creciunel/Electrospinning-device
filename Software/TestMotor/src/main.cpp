#include "main.h"

void vTaskEncoder(void *pvParameters);
void vTaskMotor(void *pvParameters);
void vTaskLCD(void *pvParameters);
void vTaskCommunication(void *pvParameters);
void vTaskTransformer(void *pvParameters);

// Motor constants
uint8_t motorSpeed = 1;       // Viteza motorului
uint8_t motorDirection = LOW; // Direcția motorului

// Transformer variables
uint8_t pwmValue = 0;

// Encoder și LCD
// Create a global pointer for the encoder object
Encoder enc(CLK, DT, SW);
LiquidCrystal_I2C lcd(ADDRESS, 16, 2);
MWCSTEPPER tb6600(ENA_PIN, DIR_PIN, PUL_PIN); // Inițializează driverul motorului

struct Flag
{
    uint8_t start = 0; // Starea de start/stop
} flag;

void setup()
{
    Serial.begin(115200);

    // Crearea sarcinilor
    xTaskCreate(vTaskEncoder, "Encoder Task", 256, NULL, 1, NULL);
    xTaskCreate(vTaskMotor, "Motor Task", 128, NULL, 1, NULL);
    xTaskCreate(vTaskLCD, "LCD Task", 128, NULL, 1, NULL);
    xTaskCreate(vTaskCommunication, "Communication Task", 128, NULL, 1, NULL);
    xTaskCreate(vTaskTransformer, "Transformer Task", 128, NULL, 1, NULL);

    // Pornește scheduler-ul FreeRTOS
    vTaskStartScheduler();

    // Setare Timer0 pentru a obține o frecvență de aproximativ 7kHz
    // Setează modul Fast PWM pentru Timer0
    TCCR0A = (1 << WGM00) | (1 << WGM01); // Mod PWM rapid
    TCCR0B = (1 << CS01) | (1 << CS00);   // Prescaler de 64

    // Initializarea LCD
    lcd.init();
    lcd.backlight();

    enc.setType(TYPE2);
}

void loop() {}

void vTaskLCD(void *pvParameters)
{
    // Initializarea LCD
    lcd.init();
    lcd.backlight();

    for (;;)
    {
        lcd.clear();

        switch (currentState)
        {
        case MAIN_MENU:
            lcd.setCursor(0, 0);
            lcd.print("1: Direction");
            lcd.setCursor(0, 1);
            lcd.print("2: Speed");
            break;

        case SELECT_DIRECTION:
            lcd.setCursor(0, 0);
            lcd.print("Direction:");
            lcd.setCursor(0, 1);
            lcd.print(motorDirection == HIGH ? "F" : "B"); // F - Forward, B - Backward
            break;

        case SELECT_SPEED:
            lcd.setCursor(0, 0);
            lcd.print("Speed:");
            lcd.setCursor(0, 1);
            lcd.print(motorSpeed); // Afișează viteza curentă
            break;

        case SENSOR_VALUES:
            lcd.setCursor(0, 0);
            lcd.print("Voltage:" + String(int(voltageValue(analogRead(ADC_PIN)) / 1000.0)));
            lcd.setCursor(0, 1);
            lcd.print("T:");
            lcd.setCursor(6, 1);
            lcd.print("H:");
            lcd.setCursor(11, 1);
            lcd.print("P:");
            break;
        }

        vTaskDelay(500 / portTICK_PERIOD_MS); // Actualizează LCD-ul la fiecare jumătate de secundă
    }
}

void vTaskMotor(void *pvParameters)
{
    digitalWrite(ENA_PIN, LOW); // Activează driverul

    for (;;)
    {
        if (flag.start)
        {
            tb6600.run(); // Rotește motorul la viteza setată
        }
        else
        {
            tb6600.active(false); // Oprește motorul
        }
        vTaskDelay(100 / portTICK_PERIOD_MS); // Delay pentru reacții rapide
    }
}

void vTaskEncoder(void *pvParameters)
{
    enc.setType(TYPE1);
    static uint32_t lastCheckTime = 0;

    for (;;)
    {
        enc.tick();

        if (millis() - lastCheckTime >= ENCODER_DELAY)
        {
            lastCheckTime = millis();

            if (enc.isSingle())
            {
                // Schimbă starea meniului la apăsare
                switch (currentState)
                {
                case MAIN_MENU:
                    currentState = SELECT_DIRECTION;
                    Serial.println("Select Direction");
                    break;
                case SELECT_DIRECTION:
                    currentState = SELECT_SPEED;
                    Serial.println("Select Speed");
                    break;
                case SELECT_SPEED:
                    currentState = MAIN_MENU;
                    Serial.println("Back to Main Menu");
                    break;
                case SENSOR_VALUES:
                    currentState = MAIN_MENU;
                    Serial.println("Back to Main Menu");
                    break;
                }
            }
            else if (enc.isDouble())
            {
                // Resetare la starea inițială
                currentState = SENSOR_VALUES;
                Serial.println("Sensor Values");

                if(flag.start){
                    flag.start = false;
                    Serial.println("Stop");
                }else{
                    flag.start = true;
                    Serial.println("Start");
                }
            }
            else if (currentState == SELECT_DIRECTION)
            {
                if (enc.isRight())
                {
                    motorDirection = HIGH; // Forward
                    Serial.println("Direction: Forward");
                }
                else if (enc.isLeft())
                {
                    motorDirection = LOW; // Backward
                    Serial.println("Direction: Backward");
                }
            }
            else if (currentState == SELECT_SPEED)
            {
                if (enc.isRight())
                {
                    motorSpeed++;
                    if (motorSpeed > 100)
                        motorSpeed = 100;
                    Serial.println("Speed: " + String(motorSpeed));
                }
                else if (enc.isLeft())
                {
                    motorSpeed--;
                    if (motorSpeed < 1)
                        motorSpeed = 1;
                    Serial.println("Speed: " + String(motorSpeed));
                }
            }
        }

        vTaskDelay(50 / portTICK_PERIOD_MS); // Întârziere pentru reacții rapide
    }
}

void vTaskTransformer(void *pvParameters)
{

    // Setează modul Fast PWM pentru Timer0
    TCCR0A = (1 << WGM00) | (1 << WGM01); // Mod PWM rapid
    TCCR0B = (1 << CS01) | (1 << CS00);   // Prescaler de 64

    pinMode(PWM_PIN, OUTPUT);

    for (;;)
    {
        analogWrite(PWM_PIN, pwmValue);
        vTaskDelay(1000 / portTICK_PERIOD_MS);
    }
}

void vTaskCommunication(void *pvParameters)
{
    Serial.println("System Initialized\r\n");

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
                digitalWrite(ENA_PIN, flag.start ? LOW : HIGH); // Activează/dezactivează driverul
                break;
            case 'd':
                motorDirection = val ? HIGH : LOW;
                tb6600.set(motorDirection == HIGH ? CLOCKWISE : COUNTERCLOCKWISE, motorSpeed, PULSE); // Setează direcția și viteza
                break;
            case 'm':
                motorSpeed = val;
                break;
            case 'p':
                pwmValue = val;
                if (pwmValue > 255)
                    pwmValue = 255;
                else if (pwmValue < 0)
                    pwmValue = 0;
                Serial.println("command: PWM, value: " + String(pwmValue));
                break;
            default:
                Serial.println("Wrong command! key: " + String(key) + ", val: " + String(val));
                break;
            }
        }
        vTaskDelay(100 / portTICK_PERIOD_MS);
    }
}