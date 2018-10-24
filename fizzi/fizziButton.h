#ifndef fizziButton_h
#define fizziButton_h
#include <Arduino.h>

// algorithm taken from https://pubweb.eng.utah.edu/~cs5780/debouncing.pdf

class fizziButton {
  public:
    fizziButton();
    void attach(byte pin);
    void update();
    void update(bool _val);
    bool press();
    bool read();
    bool rose();
    bool fell();
  private:
    bool computeRose();
    bool computeFell();
    uint8_t _pin, _roseState, _fellState;
    bool _rose = false, _fell = false, _press = false , _val = false;


};


#endif
