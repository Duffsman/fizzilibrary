#ifndef fizzi_h
#define fizzi_h


#include <Arduino.h>
#include <fizzi_boards.h>
#include <avr/pgmspace.h>
#include <avr/io.h>
#include <avr/interrupt.h>

/** @defgroup core
The Heart of Fizzi. This is where the magic happens! \n
DISCLAIMER: DO **NOT** USE delay(),micros() AND millis()!!! \n
For Accessing the pins of the MCU use **P0....P10**. P7 can only be accessed when
sync mode (USE_SYNC) is not active. P8 is also blocked because it is used for audio output.
P7 and P8 are broken out anyway so one can attach a LED for example.
*/



#ifdef USE_ENCODER
#include <RotaryEncoder.h>
RotaryEncoder encoder(ENCODER_PINA,ENCODER_PINB);
#warning "attach Encoder to P2 and P3"
#endif




// size of the audiobuffer
#ifndef BUFFERSIZE
#define BUFFERSIZE 64
#endif
// instead of writing x = t%a one can also
// write x = t&(a-1) (at least when a is power of 2)
#define BUFFERSIZEMODULO (BUFFERSIZE-1)



#define cbi(sfr, bit) (_SFR_BYTE(sfr) &= ~_BV(bit)) // clear bit
#define sbi(sfr, bit) (_SFR_BYTE(sfr) |= _BV(bit)) // set bit
#define fbi(a,b) ((a) ^= (1<<(b))) // flip bit


void initFizzi();
void initSync();
void initEncoder();
void updateFizzi();
/** @ingroup core
* DESCRIPTION: this is the place where to put the magic Formula \n
* INPUT: - \n
* RETURN: a sample
*/
byte magicFormula();
/** @ingroup core
* DESCRIPTION: when USE_SYNC is active and the sync input is active the
output sample has to be returned from this function \n
* INPUT: - \n
* RETURN:  a sample
*/
byte syncedOut();
/** @ingroup core
* DESCRIPTION: when USE_SYNC is active and the sync input is **not** active the
output sample has to be returned from this function \n
* INPUT: - \n
* RETURN:  a sample
*/
byte defaultOut();
byte (*masterOut)();
/** @ingroup core
* DESCRIPTION: this function handles eveything except computing audio samples, put all your code here \n
* INPUT: - \n
* RETURN:  -
*/
void updateControl();
/** @ingroup core
* DESCRIPTION: this function is called in updateFizzi(), can also be called more often
* in updateControl() if sound is jittering \n
* INPUT: - \n
* RETURN: -
*/
void updateBuffer();
/** @ingroup core
* DESCRIPTION: when USE_SYNC is active this function will be called once everytime a new sync pulse occurs \n
* INPUT: - \n
* RETURN: -
*/
void syncPulse();

/** @ingroup core
* DESCRIPTION: This function checks if the flag for a new sync pulse has been set.
Can also be called more often in updateControl() if the timing is not tight enough. \n
* INPUT: - \n
* RETURN: -
*/

void updateSyncPulse();

unsigned long fizziMillis();





volatile uint8_t _audioBuffer[BUFFERSIZE];
uint8_t _write = 0;
volatile uint8_t _read = 0;
volatile unsigned long _fizziMillis = 0;

/** @ingroup core
@hideinitializer
This variable is true when USE_SYNC is active and the sync input is active, too.
*/
bool isSynced = false;

volatile bool _newSyncPulse = false;

/** @ingroup core
* DESCRIPTION: setup timers and start fizzi \n
* INPUT: - \n
* RETURN: -
*/
void initFizzi() {


  #ifdef USE_SYNC
  #warning "sync activated!"
  initSync();
  #else
  #warning "sync not activated!"
  masterOut = defaultOut;
  #endif

  #ifdef USE_ENCODER
    initEncoder();
  #endif

/*
  #ifdef USE_FIZZI_ANALOG
  // set ADC-Clock prescaler to 4
  cbi(ADCSRA,ADPS2);
  //cbi(ADCSRA,ADPS1);
  // left adjust for 8-bit resolution
  sbi(ADCSRB,ADLAR);
  #warning "only use fizziAnalogRead() "
  #endif
*/
  #ifdef USE_FAST_ADC
  // set ADC-Clock prescaler to 4
  cbi(ADCSRA,ADPS2);
  #warning "FAST ADC enabled"
  #endif

  // set audio output pin as output
  pinMode(POUT,OUTPUT);
  setupTimer();

}


/*******************************/
/*            SYNC             */
/*******************************/
#ifdef USE_SYNC
void initSync() {
  // set sync input pin as input
  pinMode(PSYNC,INPUT);
  delay(10);
  // read the pin and set sync state
  bool val = digitalRead(PSYNC);
  if(val==LOW) isSynced = true;

  if(isSynced){
    masterOut = syncedOut; // output depending on sync state
    setupSync();

  }
  else masterOut = defaultOut;


}

#endif

/*******************************/
/*            UPDATE           */
/*******************************/

/** @ingroup core
* DESCRIPTION: This function handles the internals of Fizzi and is the ONLY function that has to be called in loop(). \n
* INPUT: - \n
* RETURN: -
*/
void updateFizzi(){

  updateBuffer();
  updateControl();

  // call syncPulse() on each incoming pulse when in sync mode
  #ifdef USE_SYNC
  updateSyncPulse();
  #endif

}

void updateSyncPulse(){

  if(isSynced && _newSyncPulse){
    syncPulse();
    //reset flag
    _newSyncPulse = false;

  }
}


void updateBuffer() {
  while ((_read&BUFFERSIZEMODULO) != (_write&BUFFERSIZEMODULO)){

    _audioBuffer[_write&BUFFERSIZEMODULO] = masterOut();
    _write ++;
  }

}


/*******************************/
/*         FIZZIMILLIS         */
/*******************************/
/** @ingroup core
* DESCRIPTION: Use this function as a replacement for millis().\n
* INPUT: - \n
* RETURN: Milliseonds since start of the program.
*/
unsigned long fizziMillis(){
  return _fizziMillis;
}

/*******************************/
/*   SYNC interrupt            */
/*******************************/
#ifdef USE_SYNC
uint8_t _oldState = 0x00;
ISR(SYNC_INTERRUPT){
  // read port and mask sync pin (pin 9 / PB1)
  uint8_t newState = SYNC_PIN_REG & (0x01 << 1);
  // compare new and old value
  uint8_t change = newState^_oldState;
  // if there was a change and new > old -> RISING
  if(change != 0  && newState >_oldState ){ //
    // set flag
    _newSyncPulse = true;
  }
  // update old state
  _oldState = newState;

#endif // end USE_SYNC

  #ifdef USE_ENCODER

  #if defined(__AVR_ATtiny261__)||defined(__AVR_ATtiny461__)||defined(__AVR_ATtiny861__)

      #ifndef USE_SYNC

      ISR(ENCODER_INTERRUPT){
        uint8_t newState = 0;
        uint8_t change = 0;
      #endif // end USE SYNC

  newState = ENCODER_PIN_REG & ENCODER_REG_MASK;
  change = newState ^_oldStateEnc;
  if(change != 0)
  {
    encoder.tick();
  //  if(change&(0x01 << ENCODER_L_SHIFT_A))encoder.tick();
  //  if(change&(0x01 << ENCODER_L_SHIFT_B))encoder.tick();
  }
  _oldStateEnc = newState;

    #endif // end BOARD DEF
  #endif // end USE_ENCODER


#if defined(USE_SYNC)||defined(USE_ENCODER)
}

#endif


/*******************************/
/*      sampleratetimer        */
/*******************************/

// update output and fizziMillis
ISR(TIMER_INTERRUT)
{
  // faster? modulo  modulo s.a. top
  if ((_read&0x07) == 0) _fizziMillis++;
  OUTPUT_REG = _audioBuffer[_read&BUFFERSIZEMODULO];
  _read ++;

}

/*******************************/
/*   sound helpers 'n stuff'   */
/*******************************/

/** @ingroup core
* DESCRIPTION: a very simple bitcrush effect \n
* INPUT: a sample\n
* RETURN: crushed sample
*/

inline uint8_t crush(uint8_t sample, uint8_t resolution){
  uint8_t s = 8-resolution;
  return (sample>>s)<<s;
}

/** @ingroup core
* DESCRIPTION: a function for mixing two signals together \n
* INPUT:  two samples \n
* RETURN: mixed sample
*/
inline uint8_t mix(uint8_t sampleA, uint8_t sampleB){
  uint16_t ret = (sampleA+sampleB)>>1;
  return uint8_t(ret);
}

/** @ingroup core
* DESCRIPTION: A function for modulating two signals together. For example can be used to adjust the volume of
a samplestream or for modulating two signals. \n
* INPUT:  two samples \n
* RETURN: modulated sample
*/
inline uint8_t mod(uint8_t sampleA, uint8_t sampleB){
  int ret = (sampleA *sampleB) >>8;
  return uint8_t(ret);
}



/*******************************/
/*           ENCODER           */
/*******************************/


#ifdef USE_ENCODER
void initEncoder() {


  pinMode(ENCODER_PINA,INPUT);
  pinMode(ENCODER_PINB,INPUT);

  setupEncoder();

  encoder.setPosition(0);


}


#if defined(__AVR_ATtiny84__)||defined(__AVR_ATtiny44__)|| defined(__AVR_ATtiny24__)
uint8_t _oldState0 = 0x00;
ISR(ENCODER_INTERRUPT){
  // read port and mask encoder Pins
  uint8_t newState = ENCODER_PIN_REG & ENCODER_REG_MASK;
  // compare new and old value
  uint8_t change = newState^_oldState0;

  if(change != 0){
    encoder.tick();
    //if(change&(0x01 << ENCODER_L_SHIFT_A))encoder.tick();
  //  if(change&(0x01 << ENCODER_L_SHIFT_B))encoder.tick();
  }

  // update old state
  _oldState0 = newState;
}

#endif

#endif


#endif
