#include "motor.h"

void motorsTask(void *pvParameters)
{
    (void)pvParameters;
    // setup
    motor.setSpeed(10); // 10 rpm

    // loop
    for (;;)
    {
        // Serial.println("Single coil steps");
        motor.step(100, FORWARD, SINGLE);
        motor.step(100, BACKWARD, SINGLE);

        // Serial.println("Double coil steps");
        motor.step(100, FORWARD, DOUBLE);
        motor.step(100, BACKWARD, DOUBLE);

        // Serial.println("Interleave coil steps");
        motor.step(100, FORWARD, INTERLEAVE);
        motor.step(100, BACKWARD, INTERLEAVE);

        // Serial.println("Micrsostep steps");
        motor.step(100, FORWARD, MICROSTEP);
        motor.step(100, BACKWARD, MICROSTEP);

        vTaskDelay(pdMS_TO_TICKS(1000));
    }
}