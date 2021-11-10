#include <Arduino.h>
#include "WiFi.h"

const char *SSID_ = "Totalplay-0FA5";
const char *WiFiPassword = "0FA577FBkQq8MRys";

int AnalogTemp = A3;
int DigitalTemp = 0;
float Temperature = 0;

int AnalogLight = A6;
int DigitalLight = 0;
int LightLevel =0 ;

int AnalogHum = A0;
int DigitalHum = 0;
int Humidity = 0;

void setup() {
  Serial.begin(115200);

  Serial.println();
  Serial.println();
  Serial.println();
  
  WiFi.mode(WIFI_STA);
  WiFi.begin(SSID_, WiFiPassword);
  Serial.print("Connecting to "); Serial.println(SSID_);
 
  uint8_t i = 0;
  while (WiFi.status() != WL_CONNECTED)
  {
    Serial.print('.');
    delay(500);
 
    if ((++i % 16) == 0)
    {
      Serial.println(F(" still trying to connect"));
    }
  }
 
  Serial.print(F("Connected. My IP address is: "));
  Serial.println(WiFi.localIP());
}

void loop() {
  DigitalTemp = analogRead(AnalogTemp);     // read the analog value
  Temperature = (DigitalTemp / 4096.0) * 3300 * 0.1;  // 3.3v reference and 12 bits resolution
  DigitalLight = analogRead(AnalogLight);
  LightLevel = map(DigitalLight, 0, 4095, 0, 100);
  DigitalHum = analogRead(AnalogHum);
  Humidity = map(DigitalHum, 0, 4095, 100, 0);
  Serial.print("Raw value: ");
  Serial.print(DigitalTemp);
  Serial.print("\t Temperature : ");
  Serial.print(Temperature, 2);
  Serial.print("\t Raw value: ");
  Serial.print(DigitalLight);
  Serial.print("\t Light : ");
  Serial.print(LightLevel);
  Serial.print("\t Raw value: ");
  Serial.print(DigitalHum);
  Serial.print(" \t Humidity: ");
  Serial.println(Humidity);
}
