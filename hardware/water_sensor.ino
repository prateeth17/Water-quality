#include <OneWire.h>
#include <DallasTemperature.h>

#define ONE_WIRE_BUS 4
const int pH_Pin        = 36;
const int turbidity_Pin = 39;

const float pH_Slope        = -5.0;
const float pH_Offset       = 21.34;
const float turbidity_Slope  = 7.69;
const float turbidity_Offset = 18.5;

OneWire oneWire(ONE_WIRE_BUS);
DallasTemperature sensors(&oneWire);

void setup() {
  Serial.begin(115200);
  sensors.begin();
  Serial.println("Water Quality Monitor Started");
}

void loop() {
  sensors.requestTemperatures();
  float temperature = sensors.getTempCByIndex(0);

  int pH_Raw = analogRead(pH_Pin);
  float pH_Voltage = pH_Raw * (3.3 / 4095.0);
  float pH_Value = pH_Slope * pH_Voltage + pH_Offset;

  int turb_Raw = analogRead(turbidity_Pin);
  float turb_Voltage = turb_Raw * (3.3 / 4095.0);
  float turbidity_Value = (turb_Voltage - turbidity_Offset) / turbidity_Slope;

  Serial.println("---- Sensor Readings ----");
  Serial.print("pH:          "); Serial.println(pH_Value);
  Serial.print("Turbidity:   "); Serial.print(turbidity_Value); Serial.println(" NTU");
  Serial.print("Temperature: "); Serial.print(temperature); Serial.println(" °C");

  bool ph_ok   = (pH_Value >= 6.5 && pH_Value <= 8.5);
  bool turb_ok = (turbidity_Value < 1.0);
  bool temp_ok = (temperature >= 0 && temperature <= 35);

  Serial.println((ph_ok && turb_ok && temp_ok) ? ">> SAFE TO DRINK" : ">> NOT SAFE TO DRINK");
  Serial.println("-------------------------\n");

  delay(3000);
}
