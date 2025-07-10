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

int salon = D1;


void setup() {
  Serial.begin(115200);
  connectToWiFi(ssid, password);
  setupWebSocket(server, &lastCommand);


  pinMode(salon, OUTPUT);
}

void loop() {








  Smartcommande();
  Autoupdate();
}




void Smartcommande() {

  if (!lastCommand.isEmpty()) {

    if (lastCommand == "led_on") {

      digitalWrite(salon, HIGH);
      payload.bulb1 = "true";
      Serial.println("salon est ok");


    } else if (lastCommand == "led_off") {

      digitalWrite(salon, LOW);
      payload.bulb1 = "false";
      Serial.print("salon est off");


    } else {
      // envoyer une notification
      Serial.print("notification");
      payload.notif = "okok la led recoi une commande  inconnue";
      
    }

    lastCommand = "";
    sendAutoUpdate(payload);
    payload.notif="false";
  }
}



void Autoupdate() {
  if (millis() - lastUpdateTime > updateInterval) {
    payload.ecran1 = String(millis());  // mise à jour auto
    sendAutoUpdate(payload);
    lastUpdateTime = millis();
  }
}
