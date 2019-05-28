#define VERSION "0.1"
#define TAG "arduinoesp32template"

#include "main.h"
#include <WiFiMulti.h>
#include "Arduino.h"

#include "esp_log.h"
#ifdef ARDUINO_ARCH_ESP32
#include "esp32-hal-log.h"
#endif

WiFiMulti WiFiMulti;
bool wifiConnected=false;


void setup_wifi() {
    delay(10);
    // We start by connecting to a WiFi network
    Serial.println();
    Serial.print("Connecting to ");
    Serial.println(CONFIG_ESP_WIFI_SSID);

    WiFi.mode(WIFI_STA);
    WiFiMulti.addAP(CONFIG_ESP_WIFI_SSID, CONFIG_ESP_WIFI_PASSWORD);
}


void setup(void) {

    ESP_LOGI(TAG, "Starting version " VERSION " ...");
    setup_wifi();
}



void loop() {

    if ((WiFiMulti.run() == WL_CONNECTED)) {
      if (!wifiConnected) {
        Serial.println("WiFi connected");
        Serial.println("IP address: ");
        Serial.println(WiFi.localIP());
        ESP_LOGI(TAG, "wifi done enabled %s", String(WiFi.localIP()).c_str());
        wifiConnected = true;
      }
    } else {
      wifiConnected = false;
    }
}

