#include <zephyr/kernel.h>
#include <zephyr/shell/shell.h>
#include <stdlib.h>
#include "device_params.h"

SyringePump_t motor1_pump = {
    .syringe_diameter_mm = 20.0f,
    .flow_rate_ml_h = 5.0f,
    .target_volume_ml = 10.0f,
    .is_running = false
};

SHT30_t sht30_sensor = { .temperature = 23.5f, .humidity = 45.0f };

/* Command: ls */
static int cmd_ls(const struct shell *sh, size_t argc, char **argv)
{
    shell_print(sh, "Available devices:");
    shell_print(sh, " ├── ssd1306            [Display OLED]");
    shell_print(sh, " ├── rotaryencoder       [Input Control]");
    shell_print(sh, " ├── Motor1SyringePump  [Stepper Drive]");
    shell_print(sh, " ├── Motor2Collector    [Stepper Drive]");
    shell_print(sh, " └── SHT30              [Temp/Humidity Sensor]");
    return 0;
}

/* Sub-commands for Motor1SyringePump */
static int cmd_m1_status(const struct shell *sh, size_t argc, char **argv)
{
    shell_print(sh, "--- Motor1SyringePump Status ---");
    shell_print(sh, "Syringe Diameter : %.2f mm", (double)motor1_pump.syringe_diameter_mm);
    shell_print(sh, "Flow Rate        : %.2f mL/h", (double)motor1_pump.flow_rate_ml_h);
    shell_print(sh, "Target Volume    : %.2f mL", (double)motor1_pump.target_volume_ml);
    shell_print(sh, "State            : %s", motor1_pump.is_running ? "RUNNING" : "STOPPED");
    return 0;
}

static int cmd_m1_set_flow(const struct shell *sh, size_t argc, char **argv)
{
    if (argc < 2) {
        shell_error(sh, "Usage: motor1 flow <mL/h>");
        return -EINVAL;
    }
    float val = strtof(argv[1], NULL);
    motor1_pump.flow_rate_ml_h = val;
    shell_print(sh, "Motor1 flow rate set to %.2f mL/h", (double)val);
    return 0;
}

/* Definition of Subcommands for motor1 */
SHELL_STATIC_SUBCMD_SET_CREATE(sub_motor1,
    SHELL_CMD(status, NULL, "Show Motor1 status", cmd_m1_status),
    SHELL_CMD(flow, NULL, "Set flow rate in mL/h: motor1 flow <val>", cmd_m1_set_flow),
    SHELL_SUBCMD_SET_END
);

/* Registering Root Commands */
SHELL_CMD_REGISTER(ls, NULL, "List all components", cmd_ls);
SHELL_CMD_REGISTER(motor1, &sub_motor1, "Control Motor 1 (Syringe Pump)", NULL);