#include <zephyr/kernel.h>
#include <zephyr/device.h>
#include <zephyr/drivers/display.h>
#include <zephyr/display/cfb.h>
#include <stdio.h>
#include "device_params.h"

#define DISPLAY_NODE DT_CHOSEN(zephyr_display)

static const struct device *display_dev = DEVICE_DT_GET(DISPLAY_NODE);

void display_thread_entry(void *p1, void *p2, void *p3)
{
    char buf[32];

    if (!device_is_ready(display_dev)) {
        printk("SDL Display device is not ready!\n");
        return;
    }

    /* Enable display */
    display_blanking_off(display_dev);

    if (cfb_framebuffer_init(display_dev)) {
        printk("Failed to initialize CFB!\n");
        return;
    }

    cfb_framebuffer_clear(display_dev, true);
    cfb_framebuffer_set_font(display_dev, 0);

    uint8_t font_width, font_height;
    cfb_get_font_size(display_dev, 0, &font_width, &font_height);

    while (1) {
        cfb_framebuffer_clear(display_dev, false);

        int64_t uptime_sec = k_uptime_get() / 1000;
        uint32_t hours = (uint32_t)(uptime_sec / 3600);
        uint32_t minutes = (uint32_t)((uptime_sec % 3600) / 60);

        snprintf(buf, sizeof(buf), "Uptime: %02uh %02um", hours, minutes);
        cfb_print(display_dev, buf, 0, 0);

        snprintf(buf, sizeof(buf), "Temp: %.1f C", (double)sht30_sensor.temperature);
        cfb_print(display_dev, buf, 0, font_height);

        snprintf(buf, sizeof(buf), "Humi: %.1f %%", (double)sht30_sensor.humidity);
        cfb_print(display_dev, buf, 0, font_height * 2);

        snprintf(buf, sizeof(buf), "Flow: %.1f mL/h", (double)motor1_pump.flow_rate_ml_h);
        cfb_print(display_dev, buf, 0, font_height * 3);

        cfb_framebuffer_finalize(display_dev);

        k_msleep(1000);
    }
}

K_THREAD_DEFINE(display_thread_id, 2048, display_thread_entry, NULL, NULL, NULL, 7, 0, 0);