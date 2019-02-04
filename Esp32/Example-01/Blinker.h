#ifndef Blinker_h
#define Blinker_h

#include <Ticker.h>

class Blinker{
  private:
    Ticker _ticker;
    int _ledPin = 2;
    bool _default = false;
    bool _isBlinking = false;
    float _pace = 0.1;  //seconds

  public:
    /* Construct */
    Blinker(int ledPin = 2, bool defaultValue = true);

    /* Basic Functions */
    void start(float pace);
    void stop();

    /* Class Based Functions */
    void on();
    void off();
    void setDefault(bool value);
};

#endif
