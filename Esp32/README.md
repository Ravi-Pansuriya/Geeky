# Geeky-ESP32

Geeky-ESP32 is set of examples based on Geekyworks' Smart Home (IoT) project. These examples are specially made for ESP32 module. I assume you have knowledge of writing firmware code for ESP32 using Arduino and MQTT protocol.

Examples contains basic functionalities like:
- Connect to Geekyworks' MQTT broker using **GeekyMQTT**
- Subscribe to topic and handle it's messages to control relay switches using **SwiftySwitches**.
- Publish temperature, humidity data captured using DHT11 to server.
- Receive/Transmit IR codes
- Publish ambient light(LDR) data etc...

## Dependency

- [ArduinoJson](https://arduinojson.org)
- [DHT-Sensor-Library](https://github.com/adafruit/DHT-sensor-library)
- [StringSplitter](https://github.com/aharshac/StringSplitter)
- [PubSubClient](https://github.com/knolleary/pubsubclient)
- [Shifty](https://github.com/johnnyb/Shifty)
- [GeekyMQTT](https://github.com/Ravi-Pansuriya/GeekyMQTT)
- [ShiftySwitches](https://github.com/Ravi-Pansuriya/ShiftySwitches)
- Ticker (ESP32)

Please visit [https://iot.geekyworks.com](https://iot.geekyworks.com) to setup your account and for auth-key, topic-id (controller-id) and device/sensor ids to communicate with Geekyworks' MQTT broker.

All the details regarding communication, authentication and packet structure for different devices/sensors are [here]().

## Compatible Hardware

- ESP32

## Thanks to

- Arduino Json ([ArduinoJson](https://arduinojson.org))
- Adafruit ([DHT Sensor Library](https://github.com/adafruit/DHT-sensor-library))
- Nicholas O'Leary ([PubSubClient](https://github.com/knolleary/pubsubclient))
- Jonathan Bartlett ([Shifty](https://github.com/johnnyb/Shifty))
- Harsha Alva ([StringSplitter](https://github.com/aharshac/StringSplitter))

## License

This code is released under the MIT License.
