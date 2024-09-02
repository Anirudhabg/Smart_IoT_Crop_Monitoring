// Blynk authentication token and template details
#define BLYNK_TEMPLATE_ID "YOUR_TEMPLATE_ID"
#define BLYNK_TEMPLATE_NAME "YOUR_TEMPLATE_NAME"
#define BLYNK_AUTH_TOKEN "YOUR_TEMPLATE_AUTH"

// Include necessary libraries
#include <BlynkSimpleEsp8266.h> // Blynk library
#include <ESP8266WiFi.h>        // ESP8266 WiFi library
#include <Wire.h>               // Wire library (for I2C)
#include <DHT.h>                // DHT11 Library

#define BLYNK_PRINT Serial // Blynk debug prints to Serial monitor

#define MUX_S0 5   // Pin S0 of 74HC4051 connected to NodeMCU D1
#define MUX_S1 4   // Pin S1 of 74HC4051 connected to NodeMCU D2
#define MUX_S2 14  // Pin S2 of 74HC4051 connected to NodeMCU D5
#define MUX_SIG A0 // Analog pin connected to SIG pin of 74HC4051

// Define sensor pins
#define WATER_PUMP_PIN 13 // Water Pump
#define DHT_PIN 12        // DHT11 Sensor

// WiFi credentials
char ssid[] = "********";    // Your WiFi SSID
char pass[] = "********"; // Your WiFi password
char auth[] = BLYNK_AUTH_TOKEN;

// Blynk timer
BlynkTimer timer;

// DHT sensor object
DHT dht(DHT_PIN, DHT11);

// Thresholds and calibration values
float soilThresholdValue = 25.0;                    // 25% water content
float rainThresholdValue = 60.0;                    // 60% Rain
float pHThresholdLow = 6.0;                         // Minimum acceptable pH
float pHThresholdHigh = 8.5;                        // Maximum acceptable pH
float calibrationSlope = 1.7512113655911938;        // pH calibration slope
float calibrationIntercept = 0.0014312808810704651; // pH calibration intercept

// Setup function
void setup()
{
    Serial.begin(9600);
    ESP.wdtEnable(40000);
    Serial.println("Resetting!!");
    delay(1000);

    // Connect to WiFi and Blynk
    Blynk.begin(auth, ssid, pass);
    Serial.println("Connected to Blynk!!!");
    dht.begin();

    pinMode(MUX_S0, OUTPUT);
    pinMode(MUX_S1, OUTPUT);
    pinMode(MUX_S2, OUTPUT);

    pinMode(WATER_PUMP_PIN, OUTPUT);
    digitalWrite(WATER_PUMP_PIN, HIGH); // Ensure water pump is off initially

    timer.setInterval(1000L, DHT11Sensor);
    timer.setInterval(1000L, MainFunction);
}

void DHT11Sensor()
{
    // Read temperature and humidity from DHT sensor
    float humidity = dht.readHumidity();
    float temperature = dht.readTemperature();

    // Check for valid readings
    if (isnan(humidity) || isnan(temperature))
    {
        Serial.println("Failed to read from DHT sensor!");
        return;
    }

    Blynk.virtualWrite(V0, temperature);
    Blynk.virtualWrite(V1, humidity);
}

void MainFunction()
{
    float soilMoistureSensorValue = calculateSoilMoistureValue();
    float pHSensorValue = calculatepHSensorValue();
    float rainSensorValue = calculateRainSensorValue();

    Serial.print("Soil Moisture Value: ");
    Serial.println(soilMoistureSensorValue);

    Serial.print("pH Sensor Value: ");
    Serial.println(pHSensorValue);

    Serial.print("Rain Sensor Value: ");
    Serial.println(rainSensorValue);

    Blynk.virtualWrite(V2, soilMoistureSensorValue);
    Blynk.virtualWrite(V4, pHSensorValue);

    // Check for Rain
    if (rainSensorValue > rainThresholdValue)
    {
        Blynk.logEvent("rain_alert", "Attention: Pump turned off due to heavy rain.");
        Serial.println("Heavy Rain Alert!!!");
        return;
    }

    // Check for Soil Moisture Content
    if (soilMoistureSensorValue < soilThresholdValue)
    {
        // Check for pH Levels
        if (pHSensorValue < pHThresholdLow)
        {
            Blynk.logEvent("ph_acidic_alert", "Alert: Water pH is below 6. Possible acidity detected. Please consider changing the water.");
            Serial.println("Acidic Water Content!!!");

            return;
        }
        else if (pHSensorValue > pHThresholdHigh)
        {
            Blynk.logEvent("ph_basic_alert", "Alert: Water pH Level High! Possible basic content detected. Check water quality.");
            Serial.println("Basic Water Content!!!");
            return;
        }
        else
        {
            Blynk.logEvent("soil_moisture_alert", "Attention: Water content is too low. Please water the plants.");
            Serial.println("Soil Moisture Content is Low!!!");
            return;
        }
    }
    delay(1000);
}

void selectMuxChannel(int channel)
{
    digitalWrite(MUX_S0, channel & 0x01);
    digitalWrite(MUX_S1, (channel >> 1) & 0x01);
    digitalWrite(MUX_S2, (channel >> 2) & 0x01);
}

int readSensor()
{
    int sensorValue = analogRead(MUX_SIG);
    return sensorValue;
}

float calculateSoilMoistureValue()
{
    int soilChannel = 1; // Select channel 1 (Y1) for soil moisture sensor
    selectMuxChannel(soilChannel);
    int moistureValue = readSensor();
    float mappedSoilMoistureValue = map(moistureValue, 0, 1023, 100, 0);
    return mappedSoilMoistureValue;
}

float calculatepHSensorValue()
{
    int pHChannel = 2; // Select channel 2 (Y2) for ph sensor
    selectMuxChannel(pHChannel);
    int pHValue = readSensor();
    float voltage = (pHValue * 5.0) / 1023.0;
    float mappedpHSensorValue = calibrationSlope * voltage + calibrationIntercept;
    return mappedpHSensorValue;
}

float calculateRainSensorValue()
{
    int rainChannel = 0; // Select channel 0 (Y0) for rain sensor
    selectMuxChannel(rainChannel);
    int rainValue = readSensor();
    float mappedRainValue = map(rainValue, 0, 1024, 100, 0);
    return mappedRainValue;
}

void loop()
{
    Blynk.run();
    timer.run();
}