#include "main.h"

void vTaskEncoder(void *pvParameters);
void vTaskMotor(void *pvParameters);
void vTaskLCD(void *pvParameters);
void vTaskCommunication(void *pvParameters);
void vTaskTransformer(void *pvParameters);
void vTaskSensor(void *pvParameters);

// Motor constants
uint8_t motorSpeed = 1;       // Viteza motorului
uint8_t motorDirection = LOW; // Direcția motorului

// Transformer variables
uint8_t pwmValue = 0;

float voltage = 0.0;
float temperature = 0.0;
float humidity = 0.0;
float pressure = 0.0;

// Encoder și LCD
// Create a global pointer for the encoder object
Encoder enc(CLK, DT, SW, TYPE1);
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
    xTaskCreate(vTaskEncoder, "Encoder Task", 512, NULL, 1, NULL);
    xTaskCreate(vTaskMotor, "Motor Task", 128, NULL, 1, NULL);
    xTaskCreate(vTaskLCD, "LCD Task", 128, NULL, 1, NULL);
    xTaskCreate(vTaskCommunication, "Communication Task", 128, NULL, 1, NULL);
    xTaskCreate(vTaskTransformer, "Transformer Task", 128, NULL, 1, NULL);
    xTaskCreate(vTaskSensor, "Sensor Task", 256, NULL, 1, NULL);

    // Pornește scheduler-ul FreeRTOS
    vTaskStartScheduler();

    // Setare Timer0 pentru a obține o frecvență de aproximativ 7kHz
    // Setează modul Fast PWM pentru Timer0
    TCCR0A = (1 << WGM00) | (1 << WGM01); // Mod PWM rapid
    TCCR0B = (1 << CS01) | (1 << CS00);   // Prescaler de 64

    // Initializarea LCD
    lcd.init();
    lcd.backlight();
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
            lcd.print(motorDirection == HIGH ? "Forward" : "Backward"); 
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
            lcd.print("T:" + String((int)(temperature)));
            lcd.setCursor(5, 1);
            lcd.print("H:" + String((int)(humidity)));
            lcd.setCursor(10, 1);
            lcd.print("P:" + String((int)(pressure)));
            if (flag.start)
            {
                lcd.setCursor(11, 0);
                lcd.print("Start");
            }
            else
            {
                lcd.setCursor(11, 0);
                lcd.print("Stop");
            }
            break;
        }

        vTaskDelay(500 / portTICK_PERIOD_MS); // Actualizează LCD-ul la fiecare jumătate de secundă
    }
}

void vTaskMotor(void *pvParameters)
{
    tb6600.init();
    for (;;)
    {
        tb6600.set(motorDirection == HIGH ? CLOCKWISE : COUNTERCLOCKWISE, motorSpeed, PULSE); // Setează direcția și viteza

        if (flag.start)
        {
            tb6600.run(motorSpeed); // Rotește motorul la viteza setată
        }
        else
        {
            tb6600.active(false); // Oprește motorul
        }
        vTaskDelay(20 / portTICK_PERIOD_MS); // Delay pentru reacții rapide
    }
}

void vTaskEncoder(void *pvParameters)
{
    // static uint32_t lastCheckTime = 0;

    for (;;)
    {
        enc.tick();

        // if (millis() - lastCheckTime >= ENCODER_DELAY)
        // {
        //     lastCheckTime = millis();

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

            if (flag.start)
            {
                flag.start = false;
                Serial.println("Stop");
            }
            else
            {
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
        // }

        vTaskDelay(30 / portTICK_PERIOD_MS); // Întârziere pentru reacții rapide
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

void vTaskSensor(void *pvParameters)
{
    Adafruit_BME280 bme; // Crearea obiectului BME280

    if (!bme.begin(0x76))
    { // Verifică adresa I2C
        Serial.println("Could not find a valid BME280 sensor, check wiring!");
        vTaskDelete(NULL); // Oprește task-ul dacă senzorul nu este găsit
    }

    for (;;)
    {
        // Citirea valorilor de la BME280
        temperature = bme.readTemperature(); // Asigură-te că ai inițializat senzorul BME280
        humidity = bme.readHumidity();
        pressure = bme.readPressure() / 100.0F; // Convertim la hPa

        // Afișează valorile cu o singură zecimală
        // Serial.print("Temperature: ");
        // Serial.print((int)(temperature * 10) / 10.0); // Rotunjire la o zecimală
        // Serial.print(" °C, Pressure: ");
        // Serial.print((int)(pressure * 10) / 10.0); // Rotunjire la o zecimală
        // Serial.print(" hPa, Humidity: ");
        // Serial.print((int)(humidity * 10) / 10.0); // Rotunjire la o zecimală
        // Serial.println(" %");

        vTaskDelay(2000 / portTICK_PERIOD_MS); // Actualizează datele la fiecare 2 secunde
    }
}
