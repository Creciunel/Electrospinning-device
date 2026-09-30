#ifndef DEVICE_PARAMS_H
#define DEVICE_PARAMS_H

typedef struct {
    float syringe_diameter_mm; // Syringe diameter (mm)
    float flow_rate_ml_h;      // Flow rate (mL/h)
    float target_volume_ml;    // Target volume (mL)
    float current_speed_rpm;   // Current speed (RPM)
    bool is_running;           // Running state
} SyringePump_t;

typedef struct {
    float temperature;         // Temperature (°C)
    float humidity;            // Humidity (%RH)
} SHT30_t;

extern SyringePump_t motor1_pump;
extern SHT30_t sht30_sensor;

#endif