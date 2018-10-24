#ifndef fizziMetro_h
#define fizziMetor_h


/** @defgroup fizziMetro
  A simple metronome.
*/

class fizziMetro {
public:

  /** @ingroup fizziMetro
  * DESCRIPTION: Constructor.\n
  * INPUT: - \n
  * RETURN: -
  */
  fizziMetro(){};

  /** @ingroup fizziMetro
  * DESCRIPTION: Constructor.\n
  * INPUT: length of interval in milliseconds \n
  * RETURN: -
  */

  fizziMetro(uint16_t interval){
    _interval = interval;
    _curTime = fizziMillis();
  }

  /** @ingroup fizziMetro
  * DESCRIPTION: Set duration of the interval .\n
  * INPUT: length of interval in milliseconds \n
  * RETURN: -
  */

  void setIinterval(uint16_t interval){
    _interval = interval;
  }

  /** @ingroup fizziMetro
  * DESCRIPTION: Start the metro.\n
  * INPUT: - \n
  * RETURN: -
  */
  void start() {
    _running = true;
  }

  /** @ingroup fizziMetro
  * DESCRIPTION: Stop the metro.\n
  * INPUT: - \n
  * RETURN: -
  */

  void stop() {
    _running = false;
  }

  /** @ingroup fizziMetro
  * DESCRIPTION: Get the current state of the metro, so wether it's running or not.\n
  * INPUT: - \n
  * RETURN: true when metro is running, otherwise flase.
  */
void isActive() {
  return _running;
}

/** @ingroup fizziMetro
* DESCRIPTION: Check the metro. When an interval has passed this fuction return true.\n
* INPUT: - \n
* RETURN: True when interval has passed.
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
