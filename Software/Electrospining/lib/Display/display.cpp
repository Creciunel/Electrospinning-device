#include "display.h"


Adafruit_ILI9341 tft = Adafruit_ILI9341(TFT_CS, TFT_DC, TFT_MOSI, TFT_SCLK, TFT_RST);

// For better pressure precision, we need to know the resistance
// between X+ and X- Use any multimeter to read it
// For the one we're using, its 300 ohms across the X plate
TouchScreen ts = TouchScreen(XP, YP, XM, YM, 300);

int oldcolor, currentcolor;

void displayTask(void *pvParameters)
{
    (void)pvParameters;
    
    tft.begin();
    tft.fillScreen(ILI9341_BLACK);

    // make the color selection boxes
    tft.fillRect(0, 0, BOXSIZE, BOXSIZE, ILI9341_RED);
    tft.fillRect(BOXSIZE, 0, BOXSIZE, BOXSIZE, ILI9341_YELLOW);
    tft.fillRect(BOXSIZE * 2, 0, BOXSIZE, BOXSIZE, ILI9341_GREEN);
    tft.fillRect(BOXSIZE * 3, 0, BOXSIZE, BOXSIZE, ILI9341_CYAN);
    tft.fillRect(BOXSIZE * 4, 0, BOXSIZE, BOXSIZE, ILI9341_BLUE);
    tft.fillRect(BOXSIZE * 5, 0, BOXSIZE, BOXSIZE, ILI9341_MAGENTA);

    // select the current color 'red'
    tft.drawRect(0, 0, BOXSIZE, BOXSIZE, ILI9341_WHITE);
    currentcolor = ILI9341_RED;

    for (;;)
    {
        // Retrieve a point
        TSPoint p = ts.getPoint();

        /*
         Serial.print("X = "); Serial.print(p.x);
         Serial.print("\tY = "); Serial.print(p.y);
         Serial.print("\tPressure = "); Serial.println(p.z);
        */

        // we have some minimum pressure we consider 'valid'
        // pressure of 0 means no pressing!
        if (p.z < MINPRESSURE || p.z > MAXPRESSURE)
        {
            return;
        }

        // Scale from ~0->1000 to tft.width using the calibration #'s
        p.x = map(p.x, TS_MINX, TS_MAXX, 0, tft.width());
        p.y = map(p.y, TS_MINY, TS_MAXY, 0, tft.height());

        /*
        Serial.print("("); Serial.print(p.x);
        Serial.print(", "); Serial.print(p.y);
        Serial.println(")");
        */

        if (p.y < BOXSIZE)
        {
            oldcolor = currentcolor;

            if (p.x < BOXSIZE)
            {
                currentcolor = ILI9341_RED;
                tft.drawRect(0, 0, BOXSIZE, BOXSIZE, ILI9341_WHITE);
            }
            else if (p.x < BOXSIZE * 2)
            {
                currentcolor = ILI9341_YELLOW;
                tft.drawRect(BOXSIZE, 0, BOXSIZE, BOXSIZE, ILI9341_WHITE);
            }
            else if (p.x < BOXSIZE * 3)
            {
                currentcolor = ILI9341_GREEN;
                tft.drawRect(BOXSIZE * 2, 0, BOXSIZE, BOXSIZE, ILI9341_WHITE);
            }
            else if (p.x < BOXSIZE * 4)
            {
                currentcolor = ILI9341_CYAN;
                tft.drawRect(BOXSIZE * 3, 0, BOXSIZE, BOXSIZE, ILI9341_WHITE);
            }
            else if (p.x < BOXSIZE * 5)
            {
                currentcolor = ILI9341_BLUE;
                tft.drawRect(BOXSIZE * 4, 0, BOXSIZE, BOXSIZE, ILI9341_WHITE);
            }
            else if (p.x < BOXSIZE * 6)
            {
                currentcolor = ILI9341_MAGENTA;
                tft.drawRect(BOXSIZE * 5, 0, BOXSIZE, BOXSIZE, ILI9341_WHITE);
            }

            if (oldcolor != currentcolor)
            {
                if (oldcolor == (int)ILI9341_RED)
                    tft.fillRect(0, 0, BOXSIZE, BOXSIZE, ILI9341_RED);
                if (oldcolor == (int)ILI9341_YELLOW)
                    tft.fillRect(BOXSIZE, 0, BOXSIZE, BOXSIZE, ILI9341_YELLOW);
                if (oldcolor == ILI9341_GREEN)
                    tft.fillRect(BOXSIZE * 2, 0, BOXSIZE, BOXSIZE, ILI9341_GREEN);
                if (oldcolor == ILI9341_CYAN)
                    tft.fillRect(BOXSIZE * 3, 0, BOXSIZE, BOXSIZE, ILI9341_CYAN);
                if (oldcolor == ILI9341_BLUE)
                    tft.fillRect(BOXSIZE * 4, 0, BOXSIZE, BOXSIZE, ILI9341_BLUE);
                if (oldcolor == (int)ILI9341_MAGENTA)
                    tft.fillRect(BOXSIZE * 5, 0, BOXSIZE, BOXSIZE, ILI9341_MAGENTA);
            }
        }
        if (((p.y - PENRADIUS) > BOXSIZE) && ((p.y + PENRADIUS) < tft.height()))
        {
            tft.fillCircle(p.x, p.y, PENRADIUS, currentcolor);
        }

        vTaskDelay(pdMS_TO_TICKS(1000));
    }
}