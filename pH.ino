const int pHSensorPin = A0;  // A0 pin of NodeMCU connected to the pH sensor

void setup() {
  Serial.begin(9600);
    pinMode(pHSensorPin, INPUT);
}

void loop() {
  int sensorValue = analogRead(pHSensorPin);
  
  Serial.print("Analog Value from pH Sensor: ");
  Serial.println(sensorValue);
  
  delay(1000);
}
