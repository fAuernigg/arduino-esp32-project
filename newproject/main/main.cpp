#define VERSION "0.1"
#define TAG "arduinoesp32template"

#include "main.h"
#include <WiFiMulti.h>
#include "Arduino.h"
#include <PubSubClient.h>

#include "esp_log.h"
#ifdef ARDUINO_ARCH_ESP32
#include "esp32-hal-log.h"
#endif

WiFiMulti WiFiMulti;
WiFiClient espClient;
//WiFiClientSecure espClient;

bool wifiConnected=false;
PubSubClient mqttClient(espClient);



////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////
// Add your MQTT Broker IP address and port
const char* mqtt_server = "test.mosquitto.org";
int port = 1883; //8883 for secure version
String mqtt_id;

void callback(char* topic, byte* message, unsigned int length) {
  if (String(topic) == (mqtt_id + "/somecmd")) {
    String messageTemp;
    for (int i = 0; i < length; i++) {
      Serial.print((char)message[i]);
      messageTemp += (char)message[i];
    }
    ESP_LOGI(TAG, "somecmd received found: %s, message: %s", topic, messageTemp.c_str());
  } else {
    //ESP_LOGI(TAG, "unknown topic found (skipping): %s", topic);
  }
}

void checkMqttConnected() {
  int count=0;
  // Loop until we're reconnected
  while (!mqttClient.connected() && count<2) {
    count++;
    ESP_LOGI(TAG, "Attempting MQTT connection... %i", count);

    if (mqttClient.connect(mqtt_id.c_str()))
    //if (mqttClient.connect(mqtt_id.c_str(), mqtt_user, mqtt_pass, String("offline/" + mqtt_id).c_str(), 2, true, "offline",  false))
    {
      ESP_LOGI(TAG, "connected, subscribing to topic..");
      // Subscribe
      mqttClient.subscribe(String(mqtt_id + "/#").c_str());
      // Note: publish messages to this device using
      //       mosquitto sub client: mosquitto_pub -h test.mosquitto.org -p 1883 -t "[mqtt_id]" -m "helloworld"
    } else {
      ESP_LOGE(TAG, "failed to connect, mqtt state: %i, trying again", mqttClient.state());
      // Wait x seconds before retrying
      delay(2000);
    }
  }
}
////////////////////////////////////////////////////////////


void setup_wifi() {
    delay(10);
    // We start by connecting to a WiFi network
    Serial.println();
    Serial.print("Connecting to ");
    Serial.println(CONFIG_ESP_WIFI_SSID);

    WiFi.mode(WIFI_STA);
    WiFiMulti.addAP(CONFIG_ESP_WIFI_SSID, CONFIG_ESP_WIFI_PASSWORD);

    mqttClient.setServer(mqtt_server, port);
    mqttClient.setCallback(callback);
}

void setup(void) {

    ESP_LOGI(TAG, "Starting version " VERSION " ...");
    setup_wifi();

    mqtt_id = String("testproject_") + WiFi.macAddress();
    ESP_LOGI(TAG, "Setting mqtt_id: %s", mqtt_id.c_str());
}



void loop() {

    if ((WiFiMulti.run() == WL_CONNECTED)) {
      
      checkMqttConnected();

      if (!wifiConnected) {
        Serial.println("WiFi connected");
        Serial.println("IP address: ");
        Serial.println(WiFi.localIP());
        ESP_LOGI(TAG, "wifi done enabled %s", String(WiFi.localIP()).c_str());
        wifiConnected = true;
        
        mqttClient.publish(String(mqtt_id + "/helloworld").c_str(), "helloworldmessage");
      }

      mqttClient.loop();
    } else {
      wifiConnected = false;
    }
}

