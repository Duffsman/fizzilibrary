#ifndef fizziMetro_h
#define fizziMetor_h


/** @defgroup fizziMetro
A simple metronome.
*/

class fizziMetro {
public:

  /** @ingroup fizziMetro
  constructor
  */
  fizziMetro(){};

  /** @ingroup fizziMetro
  constructor \n
  * INPUT: length of interval in milliseconds \n
  */

  fizziMetro(uint16_t interval){
    _interval = interval;
    _curTime = fizziMillis();
  }

  /** @ingroup fizziMetro
  * DESCRIPTION: set duration of the interval \n
  * INPUT: length of interval in milliseconds \n
  * RETURN: -
  */

  void setIinterval(uint16_t interval){
    _interval = interval;
  }

  /** @ingroup fizziMetro
  * DESCRIPTION: start the metro\n
  * INPUT: - \n
  * RETURN: -
  */
  void start() {
    _running = true;
  }

  /** @ingroup fizziMetro
  * DESCRIPTION: stop the metro\n
  * INPUT: - \n
  * RETURN: -
  */

  void stop() {
    _running = false;
  }

  /** @ingroup fizziMetro
  * DESCRIPTION: get the current state of the metro, so wether it's running or not\n
  * INPUT: - \n
  * RETURN: true when metro is running, otherwise flase
  */
  void isActive() {
    return _running;
  }

  /** @ingroup fizziMetro
  * DESCRIPTION: when an interval has passed this fuction returns true \n
  * INPUT: - \n
  * RETURN: true when interval has passed
  */

  bool get() {
    bool ret = false;
    if(_running){
      ret =  (fizziMillis() - _curTime) >= _interval;
      if(ret) _curTime = fizziMillis();
    }
    return ret;
  }



private:

  uint16_t _interval = 125;
  unsigned long _curTime;
  bool _running = true;

};




#endif
