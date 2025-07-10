#include "SmartESP8266Utils.h"
#include <ESP8266WiFi.h>
#include <ESPAsyncWebServer.h>

const char* ssid = "N4";
const char* password = "00000000";
// ------ variable globale ----------
AsyncWebServer server(80);
String lastCommand = "";
AutoUpdatePayload payload;
unsigned long lastUpdateTime = 0;
const unsigned long updateInterval = 500;

//------- declaration des pins --------

void setup() {
  Serial.begin(115200);
  connectToWiFi(ssid, password);
  setupWebSocket(server, &lastCommand);
  pinMode(D1, OUTPUT);
}

void loop() {








   Smartcommande();
   Autoupdate();
 
}




  void Smartcommande(){
  
  if (!lastCommand.isEmpty()) {
    if (lastCommand == "on") {
      digitalWrite(D1, HIGH);
      payload.bulb1 = "true";
      payload.ia = "OK, j’ai allumé la LED";
      payload.notif = "LED ON 💡";
    } else if (lastCommand == "off") {
      digitalWrite(D1, LOW);
      payload.bulb1 = "false";
      payload.ia = "LED éteinte";
      payload.notif = "LED OFF ❌";
    } else {
      payload.ia = "false";
      payload.notif = "false";
    }

    lastCommand = "";
    sendAutoUpdate(payload);
     payload.notif = "false";
     payload.ia = "false";
    
  }
}
void Autoupdate(){
   if (millis() - lastUpdateTime > updateInterval) {
    payload.ecran1 = String(millis()); // mise à jour auto
    sendAutoUpdate(payload);
    lastUpdateTime = millis();
  }
}
