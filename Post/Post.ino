#include <Arduino.h>
#include "WiFi.h"
#include <HTTPClient.h>

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
  //Read sensors and convert values
  DigitalTemp = analogRead(AnalogTemp);     // read the analog value
  Temperature = (DigitalTemp / 4096.0) * 3300 * 0.1;  // 3.3v reference and 12 bits resolution
  DigitalLight = analogRead(AnalogLight);
  LightLevel = map(DigitalLight, 0, 4095, 0, 100);
  DigitalHum = analogRead(AnalogHum);
  Humidity = map(DigitalHum, 0, 4095, 100, 0);

  //Construct mutation string with sensors values
  String parte1 = "{\"query\":\"mutation{createMedicion(Humedad: ";
  String query = parte1 + Humidity + ",Luz: " + LightLevel + ",Temperatura: " + Temperature + "){id}}\"}";

  if(WiFi.status() == WL_CONNECTED){
    HTTPClient http;

    Serial.print("[HTTP] begin...\n");
    
    http.begin("http://34.125.7.41:8093/graphql/"); //HTTP
    http.addHeader("Content-Type", "application/json");
    http.addHeader("Authorization", "JWT eyJ0eXAiOiJKV1QiLCJhbGciOiJIUzI1NiJ9.eyJ1c2VybmFtZSI6IkVTUDMyIiwiZXhwIjoxNjM2NTgyNTg1LCJvcmlnSWF0IjoxNjM2NTgyMjg1fQ.l2IiVxYSCmEPzpUJtsln57P-HFIKGobv3c6mUflUrv4");

    Serial.print("[HTTP] POST...\n");

    Serial.println(query);
    int httpCode = http.POST(query);   //Send the request
    String payload = http.getString();    

    // httpCode will be negative on error
    if(httpCode > 0) {
      // HTTP header has been send and Server response header has been handled
      Serial.printf("[HTTP] POST... code: %d\n", httpCode);
      /*if(httpCode == HTTP_CODE_OK) {
        Serial.println("Respuesta HTTP_CODE_OK");
        if(http.getSize()>0){
          Serial.println("Size > 0");
          String payload = http.getString();
          Serial.println("after getString()");
        }
      }*/
    }else {
      Serial.printf("[HTTP] POST... failed, error: %s\n", http.errorToString(httpCode).c_str());
    }
  }else {
    Serial.println("Not Connected...");
  }
  delay(60000);
}
