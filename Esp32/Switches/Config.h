#ifndef Config_h
#define Config_h

#define Username "<registered-email>" // https://iot.geekyworks.com
#define MyApiKey "<your-api-key>" // TODO: Change to your Geeky_IoT API Key. Your API Key is displayed on dashboard
#define TopicIdentifier "<controller-id>" // TODO: Change to Controller identifier. Your controller identifier is displayed on dashboard

// WiFi Settings
#define MySSID "<ssid>" // TODO: Change to your Wifi network SSID
#define MyWifiPassword "<password>" // TODO: Change to your Wifi network password

// Relay switch index
#define SWITCH_1  32
#define SWITCH_2  33
#define SWITCH_3  25
#define SWITCH_4  26

// MQTT host/port
const char* mqtt_host = "iot.geekyworks.com"; // Geekyworks MQTT broker
const int mqtt_port = 8085;

// Devices
// TODO: Change <switchx-id> with switch identifier you careated in dashboard
String switch1 = "<switch1-id>";
String switch2 = "<switch2-id>";
String switch3 = "<switch3-id>";
String switch4 = "<switch4-id>";

// Sensor Pins
const int LED_BUILTIN = 2;

#endif
