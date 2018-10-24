#ifndef envelope_h
#define envelope_h

#include <Arduino.h>


/** @defgroup envelope
  A simple ADSR envelope.
*/
class Envelope{

public:

  /** @ingroup envelope
  Constructor
  */
  Envelope(){
    computeIncr();
  };


  /** @ingroup envelope
    * DESCRIPTION: set paramters of the envelope \n
  * INPUT: Duration of attack, decay, sustain and release measured in samples
  * so with the default samplerate of 8000 Hz one can simply divide the set value by 8 to find out the
  * duration in milliseonds. \n
    IMPORTANT: all these values should never be 0.
  * RETURN: -
  */

  void setADSR(uint16_t a, uint16_t d, uint16_t s, uint16_t r){
    _adsr[0] = a;
    _adsr[1] = d;
    _adsr[2] = s;
    _adsr[3] = r;

    computeIncr();

  };

  /** @ingroup envelope
  * DESCRIPTION: A helper for setting the envelope more easily \n
  * INPUT: len is the total length of the tone, accent is the duration
  * of the attack phase as a percantage of the length. The attack phases
  * maximum length (when set to 255) can be 50% of the total length. \n
  * IMPORTANT: The accent and len value should never be 0. \n
  * RETURN: -
  */

  void setAccentLength(uint8_t accent, uint16_t len){
    //                            scale down, and add minimum value
    uint16_t temp = (long(len)*long((accent>>1)+20)) >>8;
    _adsr[0] = temp>>1;
    _adsr[1] = temp >>1;

    temp = (len-temp) >>1;
    _adsr[2] = temp;
    _adsr[3] = temp;

    computeIncr();


  }

  /** @ingroup envelope
  * DESCRIPTION: Set the audio level during sustain phase \n
  * INPUT: volume 0-255 \n
  * RETURN: -

  */

  void setSustainLevel(uint8_t sLvl){
    _sLvl = sLvl;
    _asDiff= 255-_sLvl;
  };


  /** @ingroup envelope
  * DESCRIPTION: Enable the envelope and start playing the note. \n
  * INPUT: - \n
  * RETURN: -

  */

  void noteOn() {
    if(_state == 4){
      _state = 0;
      _timer = _adsr[0];
      _return = 0;
    }

  };

  /** @ingroup envelope
  * DESCRIPTION: When set to true the envelope stays in sustainphase until
  * set to false again. \n
  * INPUT: true or false \n
  * RETURN: -
  */

  void hold(bool h){
    _hold = h;
  };

  /** @ingroup envelope
  * DESCRIPTION: Check if the envelope is running. \n
  * INPUT: - \n
  * RETURN: true if the envelope is running, otherwise false.
  */
  bool isActive() {

    return _state!=4;
  };

  /** @ingroup envelope
  * DESCRIPTION: Compute next value of the envelope.  \n
  * INPUT: - \n
  * RETURN: Next value of the Envelope (0-255)
  */

  uint8_t next(){

    return compute();
  };

  /** @ingroup envelope
  * DESCRIPTION: Compute next value of the envelope and apply it to a sample.  \n
  * INPUT: A sample (0-255). \n
  * RETURN: Envelope applied to sample (0-255).
  */
  uint8_t next(uint8_t sample) {

    return (compute()*sample)>>8;
  }


private:
  /* STATES
  * 0 ATTACK
  * 1 DECAY
  * 2 SUSTAIN
  * 3 RELEASE
  * 4 IDLE
  */
  uint8_t _state = 4;

  uint16_t _adsr [4] = {
    500,500,500,500
  };

  bool _hold = false;
  uint8_t _sLvl = 127;
  uint8_t _asDiff = 255-_sLvl;
  int _timer = 0;
  uint16_t _incr[3];
  int _return = 0;

  void computeIncr() {
    // compute difference between attack and sustain levle
    _asDiff = 255-_sLvl;
    // increment value from 0 to attackLevel (maximum value 255)
    _incr[0] = 65280/_adsr[0];
    // increment value from attacklevel to sustainLevel
    _incr[1] = (_asDiff<<8)/_adsr[1];
    // increment value from sustainLevel to 0
    _incr[2] = (_sLvl<<8)/_adsr[3];
  }


  uint8_t compute() {
    // change state according to _adsr times

    if((!_timer) && _state != 4){
      _state ++;
      _timer = _adsr[_state]; // hier war mal [_state%4]?!?!

    }


    switch(_state){

      case 0: // ATTACK
      _timer --;
      _return += _incr[0];
      break;

      case 1: // DECAY
      _timer --;
      _return -= _incr[1];
      break;

      case 2: // SUSTAIN
      _timer --;
      break;

      case 3: // RELEASE
      // if envelope is not in hold mode return value from release phase
      // otherwise don't change  return value
      if(!_hold){
        _timer --;
        _return -= _incr[2];
      }
      break;

      default:
      _return = 0;
      break;

    }
    return (_return >>8);
  };

};


#endif
