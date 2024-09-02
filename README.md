# Smart IoT Crop Monitoring
## Overview
This project focuses on efficient water resource management for crops using IoT technology. The system monitors soil moisture, pH levels, temperature, humidity, and rainfall to optimize water usage for irrigation.

## Components
- **Soil Moisture Sensor**
- **pH Sensor**
- **DHT11 Temperature and Humidity Sensor**
- **Rain Sensor**
- **NodeMCU ESP8266 Microcontroller**
- **CJMCU-4051 74HC4051 8 Channel Analog Multiplexer/Demultiplexer Breakout Board**

## Circuit Diagram
Give link to image


## Connections

### NodeMCU ESP8266 to CJMCU-4051 74HC4051
| CJMCU-4051 Pin      | NodeMCU ESP8266 Pin |
|---------------------|---------------------|
| VEE                 | GND                 |
| VCC                 | 3v3                 |
| GD                  | GND                 |
| Z                   | A0                  |
| S0                  | D1                  |
| S1                  | D2                  |
| S2                  | D5                  |
| E                   | GND                 |

### Sensors to CJMCU-4051 74HC4051
| Sensor       | CJMCU-4051 Pin |
|--------------|----------------|
| Rain Sensor  | Y0             |
| Soil Sensor  | Y1             |
| pH Sensor    | Y2             |

### Other Connections
| Component   | NodeMCU ESP8266 Pin |
|-------------|---------------------|
| DHT11       | D6                  |
| Relay       | D7                  |

## Setup Instructions

### Step 1: Clone the Repository
```bash
git clone https://github.com/Anirudhabg/Optimizing-Water-Management-IoT-Crop-Monitoring-System-.git
```

### Step 2: Get the Analog Values for Different Solutions
1. Make connections as shown in Image (Image Reference).
2. Get the analog values of pH for different solutions such as 4.0, 7.0, and 10.0 by using `pH.ino` code.
3. Make sure the input voltage remains the same.

### Step 3: Calculate Calibration Slope and Intercept for pH Sensor
1. Open `app.py` in your preferred IDE.
2. Run the code to calculate the calibration slope and intercept.
3. Note down the slope and intercept values.

### Step 4: Upload Code to NodeMCU
1. Open `main.ino` in Arduino IDE.
2. Enter the calculated slope and intercept values in the code.
3. Replace the Blynk template name, template ID, and auth token with your Blynk credentials.
4. Update the event names to match those in the Blynk application.
5. Set your Wi-Fi SSID and password in the code.

### Step 5: Upload the Code
1. Connect your NodeMCU ESP8266 to your computer.
2. Select the correct board and port in Arduino IDE.
3. Upload the code.

## Note
- Ensure the Blynk template name, template ID, and auth token are correctly set in the code.
- Verify that the event names in the code match those specified in the Blynk application.

## Usage
1. Power up the NodeMCU ESP8266.
2. Open the Blynk application on your mobile device.
3. Monitor real-time data for soil moisture, pH levels, temperature, humidity, and rainfall.
4. The system will automatically manage the water pump based on the sensor data to optimize irrigation.

## Troubleshooting
- **Sensor Readings Not Appearing:** Check connections and ensure all components are powered.
- **Wi-Fi Connection Issues:** Verify SSID and password are correct and that the NodeMCU is within range of the Wi-Fi network.
- **Blynk App Not Updating:** Ensure the template ID, auth token, and event names are correctly set in the code.

## Contributing
Feel free to fork this repository and submit pull requests. For major changes, please open an issue to discuss what you would like to change.

## License
This project is licensed under the MIT License.