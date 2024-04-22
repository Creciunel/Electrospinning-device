#include "motor.h"

// Connect a stepper motor with 48 steps per revolution (7.5 degree)
// to motor port #2 (M3 and M4)
AF_Stepper motor(STEPS, STEPPERNR); // uint16_t steps - revolution per steps, uint8_t num - stepper num connectet to sheeld

void motorsTask(void *pvParameters)
{
    (void)pvParameters;
    // setup
    motor.setSpeed(motorSpeed); // is good 10 rpm

    // loop
    for (;;)
    {   
        if (flag.start)
        {
            uint16_t stepsNr = runTime * motorSpeed;
            //  steps, dir, style
            motor.step(stepsNr, FORWARD, SINGLE);
        }

        vTaskDelay(pdMS_TO_TICKS(10));
    }
}