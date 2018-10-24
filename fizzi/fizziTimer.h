#ifndef fizziTimer_h
#define fizziTimer_h



/** @defgroup fizziTimer
  A simple timer.
*/
class fizziTimer{

public:

  /** @ingroup fizziTimer
constructor
  */

fizziTimer(){
    _curTime = fizziMillis();
}

/** @ingroup fizziTimer
* DESCRIPTION: get the time passed since last reset\n
* INPUT: - \n
* RETURN: time passed since last released.
*/

unsigned long get() {
  return fizziMillis()-_curTime;
}

/** @ingroup fizziTimer
* DESCRIPTION: Reset the timer to 0.\n
* INPUT: - \n
* RETURN: -
*/
void reset() {
_curTime = fizziMillis();
}


private:

  unsigned long _curTime = 0;


};



#endif
