#include <WiFi.h>
#include <WiFiMulti.h>
#include <ArduinoJson.h> // get it from https://arduinojson.org/ or install via Arduino library manager
#include <StreamString.h>
#include <DHT.h>
#include <MQTTPublisher.h>
#include "Config.h"
#include "Blinker.h"

/* Variable declarations */
uint64_t dhtTimestamp = 0;

/* Class object declarations */
WiFiMulti WiFiMulti;
WiFiClient pubClient;
MQTTPublisher publisher(pubClient, Username, MyApiKey);

// Initialize DHT sensor.
DHT dht(DHTPin, DHTTYPE);
DynamicJsonBuffer jsonBuffer;

Blinker blinker;

/* function declarations */
void WiFiEvent(WiFiEvent_t event);
void uploadSensorToServer(const char*, int, float);

/* Initialization */
void setup() {
  // put your setup code here, to run once:
  Serial.begin(115200);

  delay(10);
  pinMode(DHTPin, INPUT);
  dht.begin();  // Begin dht reading

  WiFi.onEvent(WiFiEvent);
  WiFiMulti.addAP(MySSID, MyWifiPassword);
  Serial.println();
  Serial.print("Connecting to Wifi: ");
  Serial.println(MySSID);

  blinker.start(0.3);
  // Waiting for Wifi connect
  while(WiFiMulti.run() != WL_CONNECTED) {
    delay(500);
    Serial.print(".");
  }
  if (WiFiMulti.run() == WL_CONNECTED) {
    Serial.println("");
    Serial.print("WiFi connected. ");
    Serial.print("IP address: ");
    Serial.println(WiFi.localIP());
  }
  blinker.stop();

  /* configure the MQTT server with IPaddress and port */
  publisher.setServer(mqtt_host, mqtt_port);

  delay(10);
}

/* Main program loop */
void loop() {
  if(WiFiMulti.run() == WL_CONNECTED) {
    uint64_t now = millis();
    if((now - dhtTimestamp) > DHT_INTERVAL) {
        dhtTimestamp = now;
        // Sensor readings may also be up to 2 seconds 'old' (its a very slow sensor)
        // Read temperature as Celsius (the default)
        float t = dht.readTemperature();
        Serial.printf("Temp: %.0f°c\n", t);
        if (!isnan(t)){
          // Publish temperature
          uploadSensorToServer(temperatureId, 101, t);
        }
        delay(10);
        // Read humidity
        float h = dht.readHumidity();
        Serial.printf("Humidity: %.0f%%\n", h);
        if (!isnan(h)){
          // Publish humidity
          uploadSensorToServer(humidityId, 102, h);
        }
    }
  }
}

void WiFiEvent(WiFiEvent_t event){
  Serial.printf("[WiFi-event] event: %d\n", event);

    switch (event) {
        case SYSTEM_EVENT_WIFI_READY: 
            Serial.println("WiFi interface ready");
            break;
        case SYSTEM_EVENT_SCAN_DONE:
            Serial.println("Completed scan for access points");
            break;
        case SYSTEM_EVENT_STA_START:
            Serial.println("WiFi client started");
            break;
        case SYSTEM_EVENT_STA_STOP:
            Serial.println("WiFi clients stopped");
            break;
        case SYSTEM_EVENT_STA_CONNECTED:
            Serial.println("Connected to access point");
            break;
        case SYSTEM_EVENT_STA_DISCONNECTED:
            Serial.println("Disconnected from WiFi access point");
            break;
        case SYSTEM_EVENT_STA_AUTHMODE_CHANGE:
            Serial.println("Authentication mode of access point has changed");
            break;
        case SYSTEM_EVENT_STA_GOT_IP:
            Serial.print("Obtained IP address: ");
            Serial.println(WiFi.localIP());
            break;
        case SYSTEM_EVENT_STA_LOST_IP:
            Serial.println("Lost IP address and IP address is reset to 0");
            break;
        default:
            Serial.println("Unknown");
            break;
    }
}

void uploadSensorToServer(const char* _id, int type, float val){
  Serial.println("Publishing...");
  JsonObject& root = jsonBuffer.createObject();
  root["type"] = type;
  root["client"] = publisher.clientId();
  JsonObject& data = root.createNestedObject("data");
  data["value"] = val;
  if (type == 101){
    data["unit"] = "C";
  }
  String jsonString;
  root.printTo(jsonString);
  Serial.println(jsonString);
  // Generate device topic
  String topic = String(TopicIdentifier);
  topic += "/sensors/";
  topic += _id;
  if(publisher.publish(topic, jsonString)){
    Serial.println("Published successfully..");
  } else {
    Serial.println("Publish failed!");
  }
}
