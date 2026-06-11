/*************************************************************
   Fish Quality and Spoilage Tracking Device
   ESP32 + Blynk + Sensors
 *************************************************************/

/* Blynk Device Info */
#define BLYNK_TEMPLATE_ID           "TMPL6BDBugyn3"
#define BLYNK_TEMPLATE_NAME         "Fish Quality and Spoilage Tracking Device"
#define BLYNK_AUTH_TOKEN            "hpLmy-rMiVVPawk04joBbNeY114YqNvW"

#define BLYNK_PRINT Serial

#include <WiFi.h>
#include <WiFiClient.h>
#include <BlynkSimpleEsp32.h>

#include <DHTesp.h>
#include <OneWire.h>
#include <DallasTemperature.h>

/* WiFi Credentials */
char ssid[] = "Nishan";
char pass[] = "12345678";

/* DS18B20 Temperature Sensor */
#define ONE_WIRE_BUS 18

OneWire oneWire(ONE_WIRE_BUS);
DallasTemperature sensors(&oneWire);

/* Sensor Pins */
#define PH_SENSOR_PIN        2
#define GAS_SENSOR_PIN       5
#define DHT_PIN              8

DHTesp dht;


/* LED Pins */
#define PH_WARNING_LED        7  
#define PH_CRITICAL_LED       17
#define GAS_WARNING_LED       9
#define GAS_CRITICAL_LED      10
#define HUMIDITY_WARNING_LED  11
#define HUMIDITY_CRITICAL_LED 12
#define TEMP_WARNING_LED      13
#define TEMP_CRITICAL_LED     14
#define BUZZER                19

BlynkTimer timer;

/*************************************************************
   Send Sensor Data
 *************************************************************/
void sendSensorData()
{
  // ===== Read Sensors =====
  int gasPPM = analogRead(GAS_SENSOR_PIN);

  sensors.requestTemperatures();
  float temperature = sensors.getTempCByIndex(0);

  int rawpHValue = analogRead(PH_SENSOR_PIN);
  float pHValue = map(rawpHValue, 0, 4095, 0, 140) / 10.0;

  TempAndHumidity data = dht.getTempAndHumidity();
  float humidityPercent = data.humidity;

  // ===== Send to Blynk =====
  Blynk.virtualWrite(V0, temperature);
  Blynk.virtualWrite(V1, gasPPM);
  Blynk.virtualWrite(V2, pHValue);
  Blynk.virtualWrite(V3, humidityPercent);

  // ===== Reset LEDs =====
  digitalWrite(PH_WARNING_LED, LOW);
  digitalWrite(GAS_CRITICAL_LED, LOW);
  digitalWrite(PH_CRITICAL_LED, LOW);
  digitalWrite(HUMIDITY_WARNING_LED, LOW);
  digitalWrite(HUMIDITY_CRITICAL_LED, LOW);
  digitalWrite(TEMP_CRITICAL_LED, LOW);
  digitalWrite(TEMP_WARNING_LED, LOW);
  digitalWrite(GAS_WARNING_LED, LOW);
  digitalWrite(BUZZER, LOW);

  Serial.println("================================");

  // =========================================================
  // GAS SENSOR
  // =========================================================
  if (gasPPM > 2000) {

    Serial.print("Gas Level: ");
    Serial.print(gasPPM);
    Serial.println(" PPM - HS Gas Level is High. Spoiled Fish Reported!!!");
    digitalWrite(GAS_CRITICAL_LED, HIGH);
    tone(BUZZER, 423, 1000);
    delay(500);

  } else if (gasPPM > 1500) {

    Serial.print("Gas Level: ");
    Serial.print(gasPPM);
    Serial.println(" PPM - HS Gas Level is Increasing. Check Storage");
    digitalWrite(GAS_WARNING_LED, HIGH);
    tone(BUZZER, 523, 1000);
    delay(500);

  } else {

    Serial.print("Gas Level: ");
    Serial.print(gasPPM);
    Serial.println(" PPM");
  }

  // =========================================================
  // TEMPERATURE SENSOR
  // =========================================================
  if (temperature > 6) {

    Serial.print("Temperature: ");
    Serial.print(temperature);
    Serial.println(" °C - Temperature Reached Critical Level!");
    digitalWrite(TEMP_CRITICAL_LED, HIGH);
    tone(BUZZER, 623, 1000);
    delay(500);

  } else if (temperature > 4) {

    Serial.print("Temperature: ");
    Serial.print(temperature);
    Serial.println(" °C - Temperature Warning");
    digitalWrite(TEMP_WARNING_LED, HIGH);
    tone(BUZZER, 723, 1000);
    delay(500);

  } else {

    Serial.print("Temperature: ");
    Serial.print(temperature);
    Serial.println(" °C");
  }

  // =========================================================
  // PH SENSOR
  // =========================================================
  if (pHValue < 6 || pHValue > 8) {

    Serial.print("pH Level: ");
    Serial.print(pHValue);
    Serial.println(" - CRITICAL");
    digitalWrite(PH_CRITICAL_LED, HIGH);
    tone(BUZZER, 823, 1000);
    delay(500);

  } else if ((pHValue >= 6 && pHValue < 6.5) ||
             (pHValue > 7.5 && pHValue <= 8.0)) {

    Serial.print("pH Level: ");
    Serial.print(pHValue);
    Serial.println(" - WARNING");
    digitalWrite(PH_WARNING_LED, HIGH);
    tone(BUZZER, 923, 1000);
    delay(500);

  } else {

    Serial.print("pH Level: ");
    Serial.println(pHValue);
  }

  // =========================================================
  // HUMIDITY SENSOR
  // =========================================================
  if (humidityPercent >= 90) {

    Serial.print("Humidity: ");
    Serial.print(humidityPercent);
    Serial.println("% - CRITICAL");
    digitalWrite(HUMIDITY_CRITICAL_LED, HIGH);
    tone(BUZZER, 1023, 1000);
    delay(500);

  } else if (humidityPercent > 85) {

    Serial.print("Humidity: ");
    Serial.print(humidityPercent);
    Serial.println("% - WARNING");
    digitalWrite(HUMIDITY_WARNING_LED, HIGH);
    tone(BUZZER, 1123, 1000);
    delay(500);


  } else {

    Serial.print("Humidity: ");
    Serial.print(humidityPercent);
    Serial.println("%");
  }

  Serial.println("================================");
}

void setup()
{
  Serial.begin(115200);

  // ===== Sensor Pins =====
  pinMode(PH_SENSOR_PIN, INPUT);
  pinMode(GAS_SENSOR_PIN, INPUT);
  pinMode(DHT_PIN, INPUT);

  // ===== LED Pins =====
  pinMode(PH_WARNING_LED, OUTPUT);
  pinMode(GAS_CRITICAL_LED, OUTPUT);
  pinMode(PH_CRITICAL_LED, OUTPUT);
  pinMode(HUMIDITY_WARNING_LED, OUTPUT);
  pinMode(HUMIDITY_CRITICAL_LED, OUTPUT);
  pinMode(TEMP_CRITICAL_LED, OUTPUT);
  pinMode(TEMP_WARNING_LED, OUTPUT);
  pinMode(GAS_WARNING_LED, OUTPUT);
  pinMode(BUZZER, OUTPUT);

  // ===== Start Temperature Sensor =====
  sensors.begin();

  // ===== Start DHT22 =====
  dht.setup(DHT_PIN, DHTesp::DHT22);

  // ===== Connect to WiFi + Blynk =====
  Blynk.begin(BLYNK_AUTH_TOKEN, ssid, pass);

  // ===== Send data every 2 seconds =====
  timer.setInterval(2000L, sendSensorData);

  Serial.println("Fish Quality Monitor Started");
}

void loop()
{
  Blynk.run();
  timer.run();
}