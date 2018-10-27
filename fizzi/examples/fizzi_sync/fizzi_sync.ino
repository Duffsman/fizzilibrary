
// activate SYNC mode by adding the following define
// this define has to be placed before including the fizzi.h file
#define USE_SYNC

#include<fizzi.h>
#include<FizziEnvelope.h>



// Audio output on digital Out 8 / PIN 2 / PB1
// use Attiny core by Spence Konde -> https://github.com/SpenceKonde/ATTinyCore
// by adding this link to the Board Manager -> http://drazzy.com/package_drazzy.com_index.json
/*
settings for the chip:
- Attiny 861
- External Clock 16 Mhz
- B.O.D. level: disabled
-Timer 1 Clock: 64 Mhz
- LTO: disabbled

*/

/*
  everytime a transition from LOW to HIGH occurs at the SYNC PIN (In 6 / PIN 4 / PB3) the syncPulse() function will
  be executed. In this example the envelope will be triggered.
*/

unsigned long t = 0;

fizziEnvelope env = fizziEnvelope();


void setup() {
  initFizzi();
  // set envelope
  env.setADSR(500,500,500,500);

}



void updateControl(){

  if(isSynced){};

}

byte magicFormula() {
  t++;
  int out =((t|(t>>(t%16)))>>4)& (t<<2);
  return env.next(byte(out));
}

byte defaultOut() {

  return magicFormula();
}

byte syncedOut() {

  return magicFormula();
}

void syncPulse() {
env.noteOn();

}



void loop() {

  updateFizzi();

}
