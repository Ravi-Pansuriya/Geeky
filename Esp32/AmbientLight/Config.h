#ifndef Config_h
#define Config_h

#define Username "<registered-email>" // https://iot.geekyworks.com
#define MyApiKey "<your-api-key>" // TODO: Change to your Geeky_IoT API Key. Your API Key is displayed on dashboard
#define TopicIdentifier "<controller-id>" // TODO: Change to Controller identifier. Your controller identifier is displayed on dashboard

// WiFi
#define MySSID "<ssid>" // TODO: Change to your Wifi network SSID
#define MyWifiPassword "<password>" // TODO: Change to your Wifi network password

#define LDR_INTERVAL 60000 // Set Min to 1 Minute (60Sec * 1000)

// MQTT host/port
const char* mqtt_host = "iot.geekyworks.com"; // Geekyworks MQTT broker ip
const int mqtt_port = 8085;

// Sensors
// TODO: Change <sensor-id> with ambient light sensor identifier you careated in dashboard
const char* visibilityId = "<sensor-id>";  // TODO: Change with ambiaent light sensor identifier

// Sensor Pins
const int LED_BUILTIN = 2;
const int LDRPin = 32;

#endif
