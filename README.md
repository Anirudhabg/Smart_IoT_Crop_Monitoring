# Smart IoT Crop Monitoring

## Overview
This project implements a smart system for efficient water management in crop fields using IoT technology. The system monitors essential environmental factors like soil moisture, pH levels, temperature, humidity, and rainfall to optimize irrigation practices.

## Components
- **Soil Moisture Sensor**
- **pH Sensor**
- **DHT11 Temperature and Humidity Sensor**
- **Rain Sensor**
- **NodeMCU ESP8266 Microcontroller**
- **CJMCU-4051 74HC4051 8-Channel Analog Multiplexer/Demultiplexer**

## Circuit Diagram
[Click here to view the circuit diagram](https://github.com/Anirudhabg/Smart_IoT_Crop_Monitoring/tree/dc198cc2c87d2e10e7843a34db3a78249e929be1/Images/circuit.png)

## Connections

### NodeMCU ESP8266 to CJMCU-4051 74HC4051
| CJMCU-4051 Pin | NodeMCU ESP8266 Pin |
|----------------|---------------------|
| VEE            | GND                 |
| VCC            | 3v3                 |
| GD             | GND                 |
| Z              | A0                  |
| S0             | D1                  |
| S1             | D2                  |
| S2             | D5                  |
| E              | GND                 |

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
git clone https://github.com/Anirudhabg/Smart_IoT_Crop_Monitoring.git
```

### Step 2: Obtain Analog Values for pH Solutions
1. Set up the hardware as depicted in the circuit diagram.
2. Use the `pH.ino` code to record analog values for pH solutions (e.g., 4.0, 7.0, 10.0).
3. Maintain a consistent input voltage during readings.

### Step 3: Calculate pH Sensor Calibration
1. Open `app.py` in your preferred code editor.
2. Run the script to determine the calibration slope and intercept.
3. Record these calibration parameters for later use.

### Step 4: Upload Code to NodeMCU
1. Open `main.ino` in the Arduino IDE.
2. Insert the slope and intercept values from the calibration process.
3. Update the Blynk template name, template ID, and auth token with your credentials.
4. Ensure event names in the code correspond with those in the Blynk app.
5. Enter your Wi-Fi SSID and password.

### Step 5: Upload the Code to NodeMCU
1. Connect the NodeMCU ESP8266 to your computer.
2. Choose the correct board and port in the Arduino IDE.
3. Upload the code.

## Usage
1. Power the NodeMCU ESP8266.
2. Open the Blynk app on your smartphone.
3. Monitor real-time data for soil moisture, pH, temperature, humidity, and rainfall.

## Troubleshooting
- **No Sensor Readings:** Check all connections and ensure components are receiving power.
- **Wi-Fi Issues:** Verify the SSID and password and ensure the NodeMCU is within Wi-Fi range.
- **Blynk App Not Syncing:** Confirm that the Blynk credentials and event names are correctly set.

## Contributing
Contributions are welcome! Please fork this repository and submit a pull request. For significant changes, open an issue to discuss proposed modifications.

## License
This project is licensed under the MIT License.