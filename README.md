# ESP32-S3 Electrospinning Control Device

An open-source, embedded control system for automated electrospinning setups. Powered by the **WeAct Studio ESP32-S3 (N16R8)** microcontroller, this system manages syringe pump liquid dispensing, closed-loop environmental control (temperature and humidity), rotary collector speed, and safety monitoring.

---

## Project Overview & Features

* **Syringe Pump Control**: High-precision motion driven by a **TMC2209** silent stepper driver (UART configuration + STEP/DIR interface).
* **AC Environmental Control**: Dual opto-isolated AC triac outputs (**BTA24 + MOC3041**) for 220V heating and dehumidification elements.
* **Rotary Collector Control**: High-efficiency DC motor driver via **DRV8833** dual H-bridge.
* **Environmental Sensing**: Ambient monitoring using **GXHT30 / SHT3x** (I2C) temperature and humidity sensors.
* **Safety Monitoring**: Analog NTC thermistor input (ADC) for onboard thermal monitoring and ATX power supply interlock.
* **User Interface**: 0.96" OLED display (**SSD1306** 128x64 I2C) combined with a rotary encoder for navigation.

---

## 📂 Repository Structure

| Path | Description |
| --- | --- |
| [**`Hardware/`**](Hardware/README.md) | PCB schematics, EasyEDA Pro project archive, 3D STEP models, and CAD designs. |
| ├── [**`Hardware/syringe/`**](Hardware/syringe/) | Autodesk Inventor CAD files (`.ipt`, `.iam`, `.stl`) for the syringe pump mechanism. |
| ├── [**`Hardware/easyEDA_project/`**](Hardware/easyEDA_project/) | EasyEDA Pro project backup (`.eprj2`). |
| └── [**`Hardware/3D_1-PCB...step`**](Hardware/3D_1-PCB_PCB_ESP-Electrospinning_2026-09-23.step) | 3D STEP assembly of the PCB. |
| [**`Software/`**](Software/README.md) | Firmware options for Zephyr RTOS and PlatformIO. |
| ├── [**`Software/Zephyr/`**](Software/Zephyr/) | **Zephyr RTOS v4.x** core firmware application (`app.overlay`, `prj.conf`, dual-task C sources). |
| └── [**`Software/Source_code/`**](Software/Source_code/) | Legacy PlatformIO / C++ firmware source code. |
| [**`Images/`**](Images/) | Hardware diagrams, PCB renderings, and schematic SVG previews. |
| [**`Pricing/`**](Pricing/) | Bill of Materials (BOM) and component Excel spreadsheets. |
| [**`LICENSE`**](LICENSE) | Open-source project licensing. |

---

## Visual References & Schematics

![3D_Image](Images/3D_1-PCB_PCB_ESP-Electrospinning_2026-09-24.png)

* **Schematic Diagram (SVG)**: [`Images/SCH_ESP-Electrospinning_1-Sheet_1_2026-09-24.svg`](Images/SCH_ESP-Electrospinning_1-Sheet_1_2026-09-24.svg)
* **PCB Layout 2D**: [`Images/PCB_1-PCB_PCB_ESP-Electrospinning_2026-09-24.png`](Images/PCB_1-PCB_PCB_ESP-Electrospinning_2026-09-24.png)
* **PCB 3D Render**: [`Images/3D_1-PCB_PCB_ESP-Electrospinning_2026-09-24.png`](Images/3D_1-PCB_PCB_ESP-Electrospinning_2026-09-24.png)

---

## Firmware Quick Start

### Zephyr RTOS Setup (Recommended)

```bash
cd Software/Zephyr
west build -p -b weact_esp32s3_b/esp32s3/procpu
west flash
```

### PlatformIO Setup

```bash
cd Software/Source_code
./buildPlatformIO.sh
```

---
