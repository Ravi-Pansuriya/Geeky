#ifndef Config_h
#define Config_h

#define Username "<registered-email>" // https://iot.geekyworks.com
#define MyApiKey "<your-api-key>" // TODO: Change to your Geeky_IoT API Key. Your API Key is displayed on dashboard
#define TopicIdentifier "<controller-id>" // TODO: Change to Controller identifier. Your controller identifier is displayed on dashboard

// WiFi
#define MySSID "<ssid>" // TODO: Change to your Wifi network SSID
#define MyWifiPassword "<password>" // TODO: Change to your Wifi network password

// MQTT host/port
const char* mqtt_host = "iot.geekyworks.com"; // Geekyworks MQTT broker
const int mqtt_port = 8085;

// Devices
// TODO: Change <switchx-id> with switch identifier you careated in dashboard
const char* light1 = "<device-id>"; // TODO: Change with switch identifier
const char* light2 = "<device-id>"; // TODO: Change with switch identifier
const char* light3 = "<device-id>"; // TODO: Change with switch identifier
const char* light4 = "<device-id>"; // TODO: Change with outlet identifier


// Sensor Pins
const int LED_BUILTIN = 2;

#endif
