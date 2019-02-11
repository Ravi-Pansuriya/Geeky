#include <WiFi.h>
#include <WiFiMulti.h>
#include <ArduinoJson.h> // get it from https://arduinojson.org/ or install via Arduino library manager
#include <StreamString.h>
#include <StringSplitter.h>
#include <MQTTPublisher.h>
#include <MQTTSubscriber.h>
#include "Config.h"

/* Class object declarations */
WiFiMulti WiFiMulti;
WiFiClient pubClient, subClient;
MQTTPublisher publisher(pubClient, Username, MyApiKey);
MQTTSubscriber subscriber(subClient, Username, MyApiKey);
DynamicJsonBuffer jsonBuffer;

// Declarations
void WiFiEvent(WiFiEvent_t);
void mqttCallback(String, String, byte*, unsigned int);
void turnOn(String);
void turnOff(String);
void uploadDeviceToServer(const char*, int, bool);    // To notify update back to server

void setup() {
  // put your setup code here, to run once:
  Serial.begin(115200);

  pinMode(LED_BUILTIN, OUTPUT);
  pinMode(SWITCH_1, OUTPUT);
  pinMode(SWITCH_2, OUTPUT);
  pinMode(SWITCH_3, OUTPUT);
  pinMode(SWITCH_4, OUTPUT);

  WiFi.onEvent(WiFiEvent);
  WiFiMulti.addAP(MySSID, MyWifiPassword);
  Serial.println();
  Serial.print("Connecting to Wifi: ");
  Serial.println(MySSID);

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

  /* configure subscriber with IPaddress and port of MQTT broker */
  publisher.setServer(mqtt_host, mqtt_port);
  subscriber.setServer(mqtt_host, mqtt_port);
  /* this receivedCallback function will be invoked 
  when client received subscribed topic */
  subscriber.setCallback(mqttCallback);
  // Generate device topic
  String topic = String(TopicIdentifier);
  topic += "/devices/#";
  subscriber.subscribe(topic);

}

void loop() {
  if(WiFiMulti.run() == WL_CONNECTED) {  
    /* this function will listen for incomming 
    subscribed topic-process-invoke receivedCallback */
    subscriber.loop();
  }
}

/* function implementations */
// Wifi event handler
void WiFiEvent(WiFiEvent_t event){
  Serial.printf("[WiFi-event] event: %d\n", event);
  switch (event) {
    case SYSTEM_EVENT_WIFI_READY: 
      Serial.println("WiFi interface ready");
      digitalWrite(LED_BUILTIN, LOW);
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
      digitalWrite(LED_BUILTIN, LOW);
      break;
    case SYSTEM_EVENT_STA_AUTHMODE_CHANGE:
      Serial.println("Authentication mode of access point has changed");
      break;
    case SYSTEM_EVENT_STA_GOT_IP:
      Serial.print("Obtained IP address: ");
      Serial.println(WiFi.localIP());
      digitalWrite(LED_BUILTIN, HIGH);
      break;
    default:
      digitalWrite(LED_BUILTIN, LOW);
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
  boolean value = json["data"]["power"].as<boolean>();
  if(value) {
    turnOn(deviceId);
    Serial.print("Turn on device id: ");
    Serial.println(deviceId);
  } else {
    turnOff(deviceId);
    Serial.print("Turn off device id: ");
    Serial.println(deviceId);
  }
}

// Turn on relays
void turnOn(String deviceId){
  if (deviceId == switch1) {
    digitalWrite(SWITCH_1, LOW);  
  } else if (deviceId == switch2) {
    digitalWrite(SWITCH_2, LOW);
  } else if (deviceId == switch3) {
    digitalWrite(SWITCH_3, LOW);
  } else if (deviceId == switch4) {
    digitalWrite(SWITCH_4, LOW);
  }
}

// Turn off relays
void turnOff(String deviceId){
  if (deviceId == switch1) {
    digitalWrite(SWITCH_1, HIGH);
  } else if (deviceId == switch2) {
    digitalWrite(SWITCH_2, HIGH);
  } else if (deviceId == switch3) {
    digitalWrite(SWITCH_3, HIGH);
  } else if (deviceId == switch4) {
    digitalWrite(SWITCH_4, HIGH);
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


