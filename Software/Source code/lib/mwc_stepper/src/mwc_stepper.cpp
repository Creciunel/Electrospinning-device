#include "mwc_stepper.h"
#include <Arduino_FreeRTOS.h>


MWCSTEPPER::MWCSTEPPER(uint8_t _enPin, uint8_t _dirPin, uint8_t _stepPin)
{
    stepPin = _stepPin;
    dirPin = _dirPin;
    enPin = _enPin;
}

void MWCSTEPPER::init() {
    pinMode(stepPin, OUTPUT);
    pinMode(dirPin, OUTPUT);
    pinMode(enPin, OUTPUT);
    digitalWrite(enPin, LOW);
}

void MWCSTEPPER::set(bool _dir, float _rpm, uint16_t _pulse) {
    digitalWrite(dirPin, _dir);
    rpm_t = 60000000 / (2 * _pulse * _rpm); // Calcularea timpului per pas
}

void MWCSTEPPER::run(uint64_t _rpmt) {
    digitalWrite(stepPin, HIGH);
    vTaskDelay(pdMS_TO_TICKS(_rpmt / 1000)); // Așteaptă timp în milisecunde
    digitalWrite(stepPin, LOW);
    vTaskDelay(pdMS_TO_TICKS(_rpmt / 1000)); // Așteaptă timp în milisecunde
}

void MWCSTEPPER::run() {
    digitalWrite(stepPin, HIGH);
    vTaskDelay(pdMS_TO_TICKS(rpm_t / 1000)); // Așteaptă timp în milisecunde
    digitalWrite(stepPin, LOW);
    vTaskDelay(pdMS_TO_TICKS(rpm_t / 1000)); // Așteaptă timp în milisecunde
}

void MWCSTEPPER::active(bool _active) {
    digitalWrite(enPin, _active);
}