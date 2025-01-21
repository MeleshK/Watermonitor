# Watermonitor - ESP8266-Based Ozone Generator for Groundwater Disinfection

## Overview
This project implements an **ESP8266-based ozone generator system** to disinfect groundwater pumped from a borehole. The system integrates a **flow meter** to measure the amount of water entering a storage tank and ensures **safe ozone levels** by using an ozone sensor. Excess ozone generation is prevented by automatically shutting off the ozone generator once the concentration reaches a safe threshold.

## Features
- **Automatic ozone generation** based on water flow rate
- **Real-time ozone monitoring** with an MQ131 ozone sensor
- **Automatic shutoff** to prevent excess ozone levels in water
- **Wi-Fi-enabled ESP8266** for future integration with dashboards
- **Relay-controlled solenoid valve** to regulate water flow
- **OLED display (optional)** for local monitoring
- **UltraSonic Level Kit JSN-SRT04T (optional)** for tank level sensing
- **Water and ambient air temperature sensors
- **Activated carbon filtration (recommended)** for residual ozone removal

## Components
### **Hardware**
| Component | Purpose |
|-----------|---------|
| ESP8266 (NodeMCU/D1 Mini) | Main microcontroller |
| Ozone Generator | Produces ozone for water disinfection |
| Water Flow Sensor | 5-24VDC Measures water flow rate F=7.5 * Q (Q 1-30L/min) |
| Relay Module (5V/12V) | Controls the ozone generator |
| MQ131 Ozone Sensor (or Dissolved Ozone Probe) | Measures ozone concentration |
| Ultrasonic module |
| Temp sensors x2 |
| Solenoid Valve | Controls water flow |
| OLED Display (optional) | Displays real-time status |
| Activated Carbon Filter (optional) | Removes residual ozone |
| Power Supply (5V/12V) | Powers the ESP8266 and relay |

### **Wiring Connections**
1. **Flow Sensor (model?) → ESP8266**
   - Red VCC → 5V
   - Black GND → GND
   - Yellow Signal → D2 (GPIO4)
2. **Relay Module → ESP8266**
   - VCC → 5V
   - GND → GND
   - IN → D5 (GPIO14)
3. **MQ131 Ozone Sensor → ESP8266**
   - VCC → 5V
   - GND → GND
   - AO → A0 (Analog input)
4. **Solenoid Valve → Relay Module**
   - Connect via relay to control water flow

## **Software**
### **Arduino Code**
The ESP8266 firmware is written in **Arduino IDE**. The core functionalities include:
- **Flow rate calculation** to determine water volume
- **Ozone concentration measurement** using the MQ131 sensor
- **Automatic relay control** to turn the ozone generator ON/OFF based on ozone levels
- **Serial output for debugging** and future Wi-Fi monitoring

### **Installation Instructions**
1. Install the **ESP8266 board package** in the Arduino IDE.
2. Install required libraries:
   - `ESP8266WiFi.h` (for future Wi-Fi integration)
   - `Wire.h` (for OLED display, if used)
3. Flash the firmware onto the ESP8266.
4. Power the system and test the sensor readings via Serial Monitor.

## **System Logic**
1. When water flows into the storage tank, the **flow sensor detects the rate**.
2. If water flow is detected, the **ESP8266 activates the ozone generator**.
3. The **MQ131 sensor monitors ozone concentration** in the tank.
4. If ozone **exceeds 0.5 mg/L**, the **ESP8266 turns off the ozone generator**.
5. Ultrasonic calibrated to low and high tank levels, reports in L and %
6. If necessary, the solenoid valve is also controlled before tank overflows
7. Temp sensing of water to be sampled in middle of detected flow
8. Ambient temp can either be inside tank or atmospheric
9. (Optional) Data can be **sent to a web dashboard** for remote monitoring.

## **Safety Considerations**
- Ensure **proper ventilation** to avoid ozone buildup in enclosed areas.
- Use **ozone-resistant materials** such as PTFE, PVDF, or 316L stainless steel.
- Consider adding an **activated carbon filter** for final ozone removal before consumption.
- If integrating with a Wi-Fi dashboard, ensure **secure access to the ESP8266** to prevent unauthorized control.

## **Future Improvements**
- **Wi-Fi Dashboard:** Add MQTT or Blynk for remote monitoring
- **Alarm:** Volume delivered to tank significantly lower than Avg, O3 level not increasing after Generator runtime
- **Data Logging:** Store ozone and flow data for analysis
- **Multiple Tank SUpport:** Multiple installations send data to one monitoring hub/logger
- **LCD/OLED Display:** Show real-time ozone levels and flow rates
- **PID Control:** Optimize ozone generation based on real-time feedback

## **License**
This project is open-source and available under the MIT License. Contributions and modifications are welcome!

## **Contact**
For questions or contributions, feel free to reach out or open an issue in the project repository.

