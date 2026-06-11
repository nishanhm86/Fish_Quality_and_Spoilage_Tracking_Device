Fish Quality and Spoilage Tracking Device

An IoT-based monitoring system for fish storage quality using ESP32, multiple sensors, and Blynk cloud platform. The device monitors temperature, pH levels, gas emissions (ammonia/VOCs), and humidity to detect early signs of fish spoilage.

2	Table of Contents
•	Features
•	Hardware Requirements
•	Pin Configuration
•	Software Requirements
•	Blynk Setup
•	Installation
•	Threshold Values
•	How It Works
•	Serial Output Example
•	Troubleshooting
•	Future Improvements
________________________________________

3	Features
•	Real-time Monitoring — Continuous monitoring of 4 critical parameters
•	Visual Alerts — LED indicators for warning and critical levels
•	Audible Alerts — Buzzer activates during abnormal conditions
•	Cloud Integration — Data sent to Blynk IoT platform for remote monitoring
•	Multi-parameter Detection: 
o	Temperature (DS18B20)
o	Gas/VOC levels (Spoilage detection)
o	pH levels (Fish freshness indicator)
o	Humidity levels
________________________________________

4	Hardware Requirements
Component	Quantity	Specification
ESP32 Development Board	1	Any ESP32 variant
DS18B20 Temperature Sensor	1	Waterproof recommended
MQ-135 Gas Sensor	1	For ammonia/VOC detection
pH Sensor Module	1	Analog output (0–5V)
Humidity Sensor	1	Analog output type
LEDs	8	Various colors
Buzzer	1	5V active/passive
Resistors	8	220Ω for LEDs
4.7kΩ Resistor	1	For DS18B20 data line
Breadboard & Jumper Wires	—	As needed
________________________________________

5	Pin Configuration
Component	ESP32 Pin
Sensors	
DS18B20 (Data)	18
pH Sensor	2
Gas Sensor	5
Humidity Sensor	8

Output
LEDs	
pH Warning LED	7
pH Critical LED	17
Gas Warning LED	9
Gas Critical LED	10
Humidity Warning LED	11
Humidity Critical LED	12
Temp Warning LED	13
Temp Critical LED	14	
Buzzer	19
________________________________________
6	Software Requirements
•	Arduino IDE (1.8.19 or newer)
•	ESP32 Board Package (v2.0.0 or newer)
•	Required Libraries: 
o	Blynk (Blynk_ESP32_BT_WF.h or via Library Manager)
o	OneWire (v2.3.7)
o	DallasTemperature (v3.9.0)
7	Installing Libraries
1.	Open Arduino IDE
2.	Go to Sketch → Include Library → Manage Libraries
3.	Search and install: 
o	Blynk by Volodymyr Shymanskyy
o	OneWire by Jim Studt
o	DallasTemperature by Miles Burton
8	ESP32 Board Installation
1.	Go to File → Preferences
2.	Add to "Additional Boards Manager URLs":
   https://raw.githubusercontent.com/espressif/arduino-esp32/gh-pages/package_esp32_index.json
3.	Go to Tools → Board → Boards Manager
4.	Search for esp32 and install the package by Espressif Systems
________________________________________
9	Blynk Setup
1.	Create an account at blynk.cloud
2.	Create a new Template and add the following Datastreams:
Virtual Pin	Name	Data Type
V0	Temperature	Double
V1	pH Level	Double
V2	Gas Level	Double
V3	Humidity	Double
3.	Create a new Device from the template
4.	Copy your Auth Token, Template ID, and Template Name
5.	Update the credentials in the sketch:
cpp
   #define BLYNK_TEMPLATE_ID   "YOUR_TEMPLATE_ID"
   #define BLYNK_TEMPLATE_NAME "YOUR_TEMPLATE_NAME"
   #define BLYNK_AUTH_TOKEN    "YOUR_AUTH_TOKEN"
________________________________________
10	Installation
1.	Clone or download this repository
2.	Open the .ino sketch in Arduino IDE
3.	Fill in your Wi-Fi credentials and Blynk Auth Token
4.	Select your ESP32 board under Tools → Board
5.	Select the correct Port
6.	Click Upload
7.	Open Serial Monitor at 115200 baud to view live readings
________________________________________
11	Threshold Values
These default thresholds can be adjusted in the sketch to suit your storage conditions.
11.1	Temperature (°C)
State	Value
Normal	≤ 4°C
Warning	4°C – 8°C
Critical	> 8°C
11.2	pH Level
State	Value
Normal	6.0 – 7.0
Warning	5.5 – 6.0 or 7.0 – 7.5
Critical	< 5.5 or > 7.5
11.3	Gas / VOC Level (Raw ADC)
State	Value
Normal	< 300
Warning	300 – 600
Critical	> 600
11.4	Humidity (%)
State	Value
Normal	85% – 95%
Warning	95% – 98%
Critical	> 98% or < 80%
________________________________________
12	How It Works
1.	Sensor Reading — The ESP32 reads all sensors every few seconds
2.	Threshold Evaluation — Each reading is compared against warning and critical thresholds
3.	LED Indication: 
o	🟡 Warning LED lights up when a parameter approaches unsafe levels
o	🔴 Critical LED lights up when a parameter exceeds safe limits
4.	Buzzer Alert — Activates when any parameter reaches a critical level
5.	Cloud Upload — All readings are sent to Blynk virtual pins for remote dashboard monitoring
________________________________________
13	Serial Output Example
==================================
  Fish Quality Monitor - Reading
==================================
Temperature : 3.75 °C     [OK]
pH Level    : 6.82        [OK]
Gas Level   : 214 (raw)   [OK]
Humidity    : 80.3 %      [OK]
----------------------------------
Overall Status: FRESH
==================================
________________________________________
14	Troubleshooting
Issue	Possible Cause	Solution
DS18B20 reads -127°C	Missing or incorrect pull-up resistor	Add a 4.7kΩ resistor between Data and VCC
No Blynk connection	Wrong credentials or no Wi-Fi	Check SSID, password, and auth token
pH reads 0 or erratic	Incorrect wiring or uncalibrated sensor	Verify analog pin and calibrate with buffer solutions
Gas sensor always high	Sensor needs warm-up time	Allow 2–3 minutes for MQ-135 to stabilize after power-on
LEDs not lighting up	Missing current-limiting resistors	Ensure 220Ω resistors are in series with each LED
Upload fails	Wrong board or port selected	Verify ESP32 board and COM port in Tools menu
________________________________________
15	Future Improvements
•	Add an OLED display for local status readout
•	Implement data logging to SD card or SPIFFS
•	Add push notifications via Blynk Automation
•	Integrate machine learning model for spoilage prediction
•	Support for multiple storage units via MQTT broker
•	Battery-powered operation with deep sleep mode
•	Web dashboard with historical trend graphs
•	Calibration mode accessible via serial commands
________________________________________
16	License
This project is open-source and available under the MIT License.
