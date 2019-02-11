#include "Blinker.h"
#include <Arduino.h>

inline void blink(int pin){
  digitalWrite(pin, !digitalRead(pin));
}

Blinker::Blinker(int ledPin, bool defaultValue){
  _ledPin = ledPin;
  _default = defaultValue;
  pinMode(_ledPin, OUTPUT);
  digitalWrite(_ledPin, _default);
}

void Blinker::start(float pace){
  if (!_isBlinking){
    _ticker.attach(pace, blink, _ledPin);
    _isBlinking = true;
  }
}

void Blinker::stop(){
  if (_isBlinking){
    _ticker.detach();
    _isBlinking = false;
    digitalWrite(_ledPin, _default);
  }
}

void Blinker::on(){
  digitalWrite(_ledPin, HIGH);
}

void Blinker::off(){
  digitalWrite(_ledPin, LOW);
}

void Blinker::setDefault(bool value){
  _default = value;
  digitalWrite(_ledPin, _default);
}

// Private methods


