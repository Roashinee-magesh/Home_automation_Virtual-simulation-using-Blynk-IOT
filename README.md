# Home Automation System using Blynk IoT

A complete home automation prototype built with Arduino UNO, Blynk cloud platform, and sensors/actuators. Control lights, monitor temperature and water tank levels remotely via mobile app, with automatic safety features 
## Features
Remote Control: Turn heater, cooler, inlet/outlet valves ON/OFF via Blynk app
Real-time Monitoring: Temperature gauge, water volume display on app dashboard
Auto Safety: Heater disables if temp >35°C; inlet valve activates if tank <2000L
Local Display: I2C LCD shows current temp, water volume, and device status
Light Automation: LDR-based brightness control for garden/ambient lighting

## Hardware Components
- Arduino UNO (main controller)
- LM35 temperature sensor (analog A0)
- LDR module (light sensing, analog A1)
- Ultrasonic/pressure-based water tank level sensor (serial communication)
- Relay modules (heater pin 2, cooler pin 3)
- Solenoid valves (inlet pin 4, outlet pin 5 via serial)
- I2C LCD (0x27 address, 16x2)
- Ethernet shield (for Blynk connectivity)
- LED/PWM output (garden light pin 9)

## Software Requirements
- Arduino IDE 1.8+
- PicSimLab
- Remote Serial Ports Server

## Installation
Blynk Setup:
   - Create Blynk account, new project (Template ID differs for each account user)
   - Add widgets: Buttons (V0: Heater, V1: Cooler, V2: Inlet, V3: Outlet), Gauges (V4: Temp, V5: Water Vol)
   - Copy Auth Token to code (BLYNK_AUTH_TOKEN)

Wiring in PicSimLab:
   - Connect LM35 to A0, LDR to A1
   - Relays: Heater to D2, Cooler to D3
   - Serial tank: Use SoftwareSerial or hardware UART for valve commands
   - LCD: SDA to A4, SCL to A5
   - Ethernet shield on SPI pins

## Code Structure
- home_automation_blynk_controlled.ino and main.h: Core logic, Blynk handlers, timer updates
- `ldr.cpp and lpp.hh`: Ambient light-based PWM brightness control
- `temperature_system.cpp and temperature_system.h`: LM35 reading, heater/cooler relay control
- `serial_tank.cpp and serial_tank.h`: Serial commands for tank volume/valve control


Built by [Your Name/GitHub] for IoT learning and home automation prototyping.
