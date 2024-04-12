#include "display.h"

void displayTask(void *pvParameters)
{
    // init part
    (void)pvParameters;

    ILI9341_due tft = ILI9341_due(CS_PIN, CD_PIN, RESET_PIN);

    status = tft.begin();

    if (!status)
        Serial.println("-1, TFT display error");

    tft.setRotation(iliRotation270);
    tft.fillScreen(ILI9341_BLUE);

    tft.setFont(Arial_bold_14);
    tft.setTextLetterSpacing(5);
    tft.setTextColor(ILI9341_WHITE, ILI9341_BLUE);
    tft.printAligned(F("Hello World"), gTextAlignMiddleCenter);
    // loop part
    for (;;)
    {
        vTaskDelay(pdMS_TO_TICKS(1000));
    }
}