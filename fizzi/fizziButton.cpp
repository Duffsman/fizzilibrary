#include "fizziButton.h"

/** @defgroup fizziButton
  A simple Button debounce that does not rely on millis()
*/

/** @ingroup fizziButton
*constructor
*/
fizziButton::fizziButton() {}

/**  @ingroup fizziButton
* DESCRIPTION:  attach pin to the Button object.\n
* INPUT:  the pin to read \n
* RETURN: -
*/

void fizziButton::attach(byte pin) {
  _pin = pin;
  computeRose();
  computeFell();
}

/**  @ingroup fizziButton
* DESCRIPTION: update button state\n
* INPUT: - \n
* RETURN: -
*/

void fizziButton::update() {
  _val = digitalRead(_pin);
  _rose = computeRose();
  _fell = computeFell();

}

/**  @ingroup fizziButton
* DESCRIPTION: update button state\n
* INPUT:  a value e.g. read from a pin \n
* RETURN: -
*/

void fizziButton::update(bool val) {
  _val = val;
  _rose = computeRose();
  _fell = computeFell();

}
// source: https://pubweb.eng.utah.edu/~cs5780/debouncing.pdf

bool fizziButton::computeRose() {

  _roseState=(_roseState<<1) | (!_val) | 0xF0;
  if(_roseState==0xF8){
    _press = true;
    return true;
  }
  return false;
}


bool fizziButton::computeFell() {

  _fellState=(  _fellState<<1) | (_val) | 0xF0;
  if(  _fellState==0xF8){
    _press = false;
    return true;
  }
  return false;
}

/**  @ingroup fizziButton
* DESCRIPTION: get the current state of the button\n
* INPUT: - \n
* RETURN: true or false, depending on the way the button is connected (pullup or pulldown)
*/

bool fizziButton::press() {

  return _press;
}

/**  @ingroup fizziButton
* DESCRIPTION: get the current state of the button.\n
* INPUT: - \n
* RETURN: true or false, depending on the way the button is connected (pullup or pulldown)
*/
bool fizziButton::read() {
  return _press;
}

/**  @ingroup fizziButton
* DESCRIPTION: get when the button pin fell\n
* INPUT: - \n
* RETURN: true when there was a transition from HIGH to LOW
*/
bool fizziButton::fell(){
  return _fell;
}
/**  @ingroup fizziButton
* DESCRIPTION: get when the button pin rose\n
* INPUT: - \n
* RETURN: true when there was a transition from LOW to HIGH
*/
bool fizziButton::rose(){
  return _rose;
}
