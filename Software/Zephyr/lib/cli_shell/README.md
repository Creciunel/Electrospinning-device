uart:~$ ls
Available devices:
 ├── ssd1306            [Display OLED]
 ├── rotaryencoder       [Input Control]
 ├── Motor1SyringePump  [Stepper Drive]
 ├── Motor2Collector    [Stepper Drive]
 └── SHT30              [Temp/Humidity Sensor]

uart:~$ motor1 status
--- Motor1SyringePump Status ---
Syringe Diameter : 20.00 mm
Flow Rate        : 5.00 mL/h
Target Volume    : 10.00 mL
State            : STOPPED

uart:~$ motor1 flow 12.5
Motor1 flow rate set to 12.50 mL/h

uart:~$ motor1 status
--- Motor1SyringePump Status ---
...
Flow Rate        : 12.50 mL/h