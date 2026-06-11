## Fish Quality and Spoilage Tracking Device

An IoT-based monitoring system for fish storage quality using ESP32, multiple sensors, and Blynk cloud platform. The device monitors temperature, pH levels, gas emissions (ammonia/VOCs), and humidity to detect early signs of fish spoilage.

## Table of Contents
1. Features
2. Hardware Requirements
3. Pin Configuration
4. Software Requirements
5. Blynk Setup
6. Installation
7. Threshold Values
8. How It Works
9. Troubleshooting
10. Future Improvements

________________________________________

## 1. Features
1. Real-time Monitoring — Continuous monitoring of 4 critical parameters
2. Visual Alerts — LED indicators for warning and critical levels
3. Audible Alerts — Buzzer activates during abnormal conditions
4. Cloud Integration — Data sent to Blynk IoT platform for remote monitoring
5. Multi-parameter Detection:
6. Temperature (DS18B20)
7. Gas/VOC levels (Spoilage detection)
8. pH levels (Fish freshness indicator)
9. Humidity levels

________________________________________

## 2. Hardware Requirements

| Component | Quantity | Specification |
|----------|----------|---------------|
| ESP32 Development Board | 1 | Any ESP32 variant |
| DS18B20 Temperature Sensor | 1 | Waterproof recommended |
| MQ-135 Gas Sensor | 1 | For ammonia/VOC detection |
| pH Sensor Module | 1 | Analog output (0–5V) |
| Humidity Sensor | 1 | Analog output type |
| LEDs | 8 | Various colors |
| Buzzer | 1 | 5V active/passive |
| Resistors | 8 | 220Ω for LEDs |
| 4.7kΩ Resistor | 1 | For DS18B20 data line |
| Breadboard & Jumper Wires | As needed | - |

________________________________________

## 3. Pin Configuration

1. Component	ESP32 Pin

### Sensors	

1. DS18B20 (Data)	18
2. pH Sensor	2
3. Gas Sensor	5
4. Humidity Sensor	8

### Output

1. pH Warning LED	7
2. pH Critical LED	17
3. Gas Warning LED	9
4. Gas Critical LED	10
5. Humidity Warning LED	11
6. Humidity Critical LED	12
7. Temp Warning LED	13
8. Temp Critical LED	14
9. Buzzer	19

________________________________________

## 4. Software Requirements

1. Arduino IDE (1.8.19 or newer)
   
3. ESP32 Board Package (v2.0.0 or newer)
   
4. Required Libraries:

   3.1 Blynk (Blynk_ESP32_BT_WF.h or via Library Manager)

   3.2 OneWire (v2.3.7)

   3.3 DallasTemperature (v3.9.0)

________________________________________

### 4.1 Installing Libraries

1. Open Arduino IDE
2. Go to Sketch → Include Library → Manage Libraries
3. Search and install: 
o	Blynk by Volodymyr Shymanskyy
o	OneWire by Jim Studt
o	DallasTemperature by Miles Burton

________________________________________

### 4.2 ESP32 Board Installation
1.	Go to File → Preferences
2.	Add to "Additional Boards Manager URLs":
   https://raw.githubusercontent.com/espressif/arduino-esp32/gh-pages/package_esp32_index.json
3.	Go to Tools → Board → Boards Manager
4.	Search for esp32 and install the package by Espressif Systems

________________________________________

## 5. Blynk Setup

1.	Create an account at blynk.cloud
   
3.	Create a new Template and add the following Datastreams:
   
Virtual Pin	            Name              Data Type

1. V0	               Temperature	         Double
2. V1	               pH Level	            Double
3. V2	               Gas Level         	Double
4. V3	               Humidity	            Double

6.	Create a new Device from the template
7.	Copy your Auth Token, Template ID, and Template Name
8.	Update the credentials in the sketch:

cpp

   #define BLYNK_TEMPLATE_ID   "YOUR_TEMPLATE_ID"

   #define BLYNK_TEMPLATE_NAME "YOUR_TEMPLATE_NAME"
   
   #define BLYNK_AUTH_TOKEN    "YOUR_AUTH_TOKEN"
  	
________________________________________

## 6. Installation
1.	Clone or download this repository
2.	Open the .ino sketch in Arduino IDE
3.	Fill in your Wi-Fi credentials and Blynk Auth Token
4.	Select your ESP32 board under Tools → Board
5.	Select the correct Port
6.	Click Upload
7.	Open Serial Monitor at 115200 baud to view live readings

________________________________________

## 7. Threshold Values

These default thresholds can be adjusted in the sketch to suit your storage conditions.

| Parameter | Normal | Warning | Critical |
|----------|--------|---------|----------|
| Temperature (°C) | ≤ 4°C | 4°C – 8°C | > 8°C |
| pH Level | 6.0 – 7.0 | 5.5 – 6.0 or 7.0 – 7.5 | < 5.5 or > 7.5 |
| Gas / VOC (ADC) | < 300 | 300 – 600 | > 600 |
| Humidity (%) | 85% – 95% | 95% – 98% | > 98% or < 80% |

________________________________________

## 8. How It Works

1.	Sensor Reading — The ESP32 reads all sensors every few seconds

2.	Threshold Evaluation — Each reading is compared against warning and critical thresholds

3.	LED Indication:
   
o	🟡 Warning LED lights up when a parameter approaches unsafe levels

o	🔴 Critical LED lights up when a parameter exceeds safe limits

5.	Buzzer Alert — Activates when any parameter reaches a critical level

6.	Cloud Upload — All readings are sent to Blynk virtual pins for remote dashboard monitoring
________________________________________

## 9. Troubleshooting

| Issue | Possible Cause | Solution |
|------|----------------|----------|
| DS18B20 reads -127°C | Missing or incorrect pull-up resistor | Add a 4.7kΩ resistor between Data and VCC |
| No Blynk connection | Wrong credentials or no Wi-Fi | Check SSID, password, and auth token |
| pH reads 0 or is erratic | Incorrect wiring or uncalibrated sensor | Verify the analog pin and calibrate with buffer solutions |
| Gas sensor always high | Sensor needs warm-up time | Allow 2–3 minutes for MQ-135 to stabilize after power-on |
| LEDs not lighting up | Missing current-limiting resistors | Ensure 220Ω resistors are in series with each LED |
| Upload fails | Wrong board or port selected | Verify ESP32 board and COM port in Tools menu |

________________________________________

## 10. Future Improvements

1. Add an OLED display for local status readout
2. Implement data logging to the SD card or SPIFFS
3. Add push notifications via Blynk Automation
4. Integrate a machine learning model for spoilage prediction
5. Support for multiple storage units via MQTT broker
6. Battery-powered operation with deep sleep mode
7. Web dashboard with historical trend graphs
8. Calibration mode accessible via serial commands

________________________________________

## License

This project is open-source and available under the MIT License.
