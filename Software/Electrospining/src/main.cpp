#include <config.h>

static void displayTask(void *pvParameters);
static void voltageMasureTask(void *pvParameters);
static void motorsTask(void *pvParameters);

void setup(void)
{
  Serial.begin(115200);

  xTaskCreate(displayTask, "Dysplay info", 100, NULL, 1, NULL);
  xTaskCreate(voltageMasureTask, "Masure voltage", 100, NULL, 1, NULL);
  xTaskCreate(motorsTask, "Connect motors", 100, NULL, 1, NULL);
}

void loop(void)
{

  vTaskDelay(100);
}

static void displayTask(void *pvParameters)
{
  // init part
  ILI9341_due tft = ILI9341_due(CS_PIN, CD_PIN, RESET_PIN);

  bool result = tft.begin();

  Serial.print("TFT begin successful: ");
  Serial.println(result ? "YES" : "NO");

  tft.setRotation(iliRotation270);
  tft.fillScreen(ILI9341_BLUE);

  tft.setFont(Arial_bold_14);
  tft.setTextLetterSpacing(5);
  tft.setTextColor(ILI9341_WHITE, ILI9341_BLUE);
  tft.printAligned(F("Hello World"), gTextAlignMiddleCenter);
  // loop part
  for (;;)
  {
    vTaskDelay(100);
  }
}
static void voltageMasureTask(void *pvParameters)
{
}
static void motorsTask(void *pvParameters)
{
}