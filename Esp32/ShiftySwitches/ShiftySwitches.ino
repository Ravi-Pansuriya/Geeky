#include <WiFi.h>
#include <WiFiMulti.h>
#include <ArduinoJson.h> // get it from https://arduinojson.org/ or install via Arduino library manager
#include <StreamString.h>
#include <Shifty.h>
#include <StringSplitter.h>
#include <ShiftySwitches.h>
#include <MQTTPublisher.h>
#include <MQTTSubscriber.h>
#include "Config.h"
#include "Blinker.h"

/* Class object declarations */
WiFiMulti WiFiMulti;
WiFiClient pubClient, subClient;
MQTTPublisher publisher(pubClient, Username, MyApiKey);
MQTTSubscriber subscriber(subClient, Username, MyApiKey);

ShiftySwitches switches;
DynamicJsonBuffer jsonBuffer;

Blinker blinker;

/* function declarations */
void WiFiEvent(WiFiEvent_t event);
void mqttCallback(String topic, String deviceId, byte* payload, unsigned int length);
void uploadDeviceToServer(const char*, int, bool);    // To notify update back to server

/* Initialization */
void setup() {
  // put your setup code here, to run once:
  Serial.begin(115200);

  delay(10);

  // Add switch ids
  switches.add(light1, 0);
  switches.add(light2, 1);
  switches.add(light3, 2);
  switches.add(light4, 3);

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
  subscriber.setServer(mqtt_host, mqtt_port);
  /* this receivedCallback function will be invoked 
  when client received subscribed topic */
  subscriber.setCallback(mqttCallback);
  // Generate device topic
  String topic = String(TopicIdentifier);
  topic += "/device/#";
  subscriber.subscribe(topic);

  delay(10);
}

/* Main program loop */
void loop() {
  if(WiFiMulti.run() == WL_CONNECTED) {  
    /* this function will listen for incomming 
    subscribed topic-process-invoke receivedCallback */
    subscriber.loop();
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

void mqttCallback(String topic, String deviceId, byte* payload, unsigned int length) {
  // handle message arrived
  Serial.print("Message received: ");
  Serial.println(topic);
  Serial.print("payload: ");
  for (int i = 0; i < length; i++) {
    Serial.print((char)payload[i]);
  }
  Serial.println("");
  
  // Parse payload buffer
  JsonObject& json = jsonBuffer.parseObject((char*)payload); 
  String clientId = json["client"];
  if (clientId != publisher.clientId()) {
    boolean value = json["data"]["power"].as<boolean>();
    if(value) {
      if(!switches.turnOn(deviceId)){
        Serial.print("Turn on device id: ");
        Serial.println(deviceId);
      }
    } else {
      if(!switches.turnOff(deviceId)){
        Serial.print("Turn off device id: ");
        Serial.println(deviceId);
      }
    }
  }
}

// Call this function to notify device update to server.
// if you have implemented push buttons, IR remote ar anything else that invoke device value updates locally.
// i.e. uploadDeviceToServer(SWITCH_1, 1, true);
void uploadDeviceToServer(const char* _id, int type, bool val){
  Serial.println("Publishing...");
  JsonObject& root = jsonBuffer.createObject();
  root["type"] = type;
  root["client"] = publisher.clientId();
  JsonObject& data = root.createNestedObject("data");
  data["power"] = val;
  String jsonString;
  root.printTo(jsonString);
  Serial.println(jsonString);
  // Generate device topic
  String topic = String(TopicIdentifier);
  topic += "/devices/";
  topic += _id;
  if(publisher.publish(topic, jsonString)){
    Serial.println("Published successfully..");
  } else {
    Serial.println("Publish failed!");
  }
}
