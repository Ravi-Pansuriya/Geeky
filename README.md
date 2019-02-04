# Geeky

[![Geekyworks](https://cldup.com/dTxpPi9lDf.thumb.png)](https://geekyworks.com)

Geeky helps you to intigrate devices with Amazon Alexa, Google Home and personalized web panel provided by [Geekyworks](https://iot.geekyworks.com). It's made for hobbyist and enthusiastic iot developers. With geeky you can control development boards directly such as ESP32, ESP8266, RaspberryPi or any boards that supports WiFi or Ethernet via amazing support of [MQTT](http://mqtt.org/).

The service provided by Geekyworks is totally free but has limited functionalities and will be improved in future with your support. Geeky has also got mobile apps ready for Android and iOS.

# Documentation

- Please check [**'How to use?'**]() guide for implementation

### Features!
- Control devices via Amazon Alexa, Google Home, Mobile and Web Panel
- Easy MQTT implementation with predefined common message structure
- Server remembers last status of device
- Report device status back to server

### Examples
- [ESP32](https://github.com/Ravi-Pansuriya/Geeky-ESP32/tree/master/Esp32)

(More examples are coming in future)

### Dependencies
Public libraries:
- [ArduinoJson](https://arduinojson.org)
- [DHT-Sensor-Library](https://github.com/adafruit/DHT-sensor-library)
- [StringSplitter](https://github.com/aharshac/StringSplitter)
- [PubSubClient](https://github.com/knolleary/pubsubclient)
- [Shifty](https://github.com/johnnyb/Shifty)
- Ticker (ESP32)

Geeky wrapper libraries:
- [GeekyMQTT](https://github.com/Ravi-Pansuriya/GeekyMQTT)
- [ShiftySwitches](https://github.com/Ravi-Pansuriya/ShiftySwitches)

Please visit [https://iot.geekyworks.com](https://iot.geekyworks.com) to setup your account and for auth-key, topic-id (controller-id) and device/sensor ids to communicate with Geekyworks' MQTT broker.

All the details regarding communication, authentication and packet structure for different devices/sensors are [here]().

### Compatible Hardware
- ESP32
- ESP8266
- RaspberryPi
- Any other board with WiFi/Ethernet support

### To Do
- Report status update to Amazon Alexa and Google Home
- Add secure SSL connection support over MQTT connection
- Add support for:
    - Thermostat
    - Television
    - Speaker
    - Window Shutter
    - Scene

### Thanks to
