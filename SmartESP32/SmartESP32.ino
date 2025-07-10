#include "SmartESP32Utils.h"


// ------ Connexion WiFi --------
const char* ssid = "N4";
const char* password = "00000000";

// ------ Variables globales ------
AsyncWebServer server(80);
String lastCommand = "";
AutoUpdatePayload payload;
unsigned long lastUpdateTime = 0;
const unsigned long updateInterval = 500;

// ------- Déclaration des pins --------
// Choisis un GPIO dispo pour la LED, par exemple GPIO 23
int salon = 23;

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
      Serial.println("salon est off");

    } else {
      Serial.println("notification");
      payload.notif = "okok la led recoi une commande inconnue";
    }

    lastCommand = "";
    sendAutoUpdate(payload);
    payload.notif = "false";
  }
}

void Autoupdate() {
  if (millis() - lastUpdateTime > updateInterval) {
    payload.ecran1 = String(millis());
    sendAutoUpdate(payload);
    lastUpdateTime = millis();
  }
}
