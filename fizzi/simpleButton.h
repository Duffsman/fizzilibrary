#ifndef simpleButton_h
#define simpleButton_h
#include <Arduino.h>


class simpleButton {
public:
  simpleButton(){};
  void update(bool _val){

    if (_val > _oldval) _rose = true;
    else _rose = false;

    if (_val < _oldval) _fell = true;
    else _fell = false;

    _oldval = _val;


  };
  bool press(){
    return _oldval;
  };
  bool rose(){
    return _rose;
  };
  bool fell(){
    return _fell;
  };
private:
  bool _oldval = false, _rose = false, _fell = false;

};


#endif
