#ifndef fizziGlide_h
#define fizziGlide_h
#include <Arduino.h>


/** @defgroup fizziGlide
an object for linear interpolating a value from start to stop over a given number if steps
*/

class fizziGlide{
public:

  /** @ingroup fizziGlide
  constructor
  */
  fizziGlide(){};

/** @ingroup fizziGlide
DESCRIPTION: set the glide object \n
INPUT: start value (0...255), stop value (0...255), and legnth (0...65.565) \n
OUTPUT: -
*/
  void set(uint8_t start, uint8_t stop, uint16_t length) {
    _start = start;
    _stop = stop;
    _incr = abs(_start - _stop);
    _incr =(_incr<<8)/length;
    if(start > stop)_f = -1;
    else _f = 1;


  };

  /** @ingroup fizziGlide
  DESCRIPTION: current status of the glide \n
  INPUT: - \n
  OUTPUT: true if glide is active, otherwise false
  */

  bool isActive(){
    return _isOn;
  };

  /** @ingroup fizziGlide
  DESCRIPTION: start the glide; can only be startetd when the previous glide is finished \n
  INPUT: -\n
  OUTPUT: -
  */

  void glideOn(){
    if(!_isOn){
      _isOn = true;
      _ret = _start;
      _t = 0;
    }
  };

  /** @ingroup fizziGlide
  DESCRIPTION: compute the next value for the glide when the glide is finished this function returns the stop value \n
  INPUT: -\n
  OUTPUT: next value (0...255)
  */
  uint16_t next(){
    if(_ret != _stop){
      _t+= _incr;
      _ret =_start+ (_f*(_t>>8));
    } else{
      _isOn = false;
    }
    return _ret;
  };

private:
  uint8_t _start, _stop, _ret;
  int8_t _f = 1;
  int _incr;
  int _t;
  bool _isOn = false;



};


#endif
