#include <Arduino.h>
#include "WiFi.h"

const char *SSID_ = "Totalplay-0FA5";
const char *WiFiPassword = "0FA577FBkQq8MRys";

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

}
