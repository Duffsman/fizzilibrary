// for activating the encoder add this define
// this define has to be placed before including the fizzi.h file
#define USE_ENCODER

#include<fizzi.h>

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


Connect Encoder A and B to P2 and P3

*/
unsigned long t = 0;
int encPos = 0;


void setup() {
  initFizzi();

}



void updateControl(){


  // update encPos if encoder position has changed
  if(encoder.getPosition() != 0){
    encPos += encoder.getPosition();
    encPos = constrain(encPos,0,14);
    encoder.setPosition(0);
  }




}

byte magicFormula() {
  t++;
  int out =((t<<encPos|t>>4)&t>>2);
  return byte(out);
}

byte defaultOut() {

  return magicFormula();
}

byte syncedOut() {

  return magicFormula();
}

void syncPulse() {


}



void loop() {

  updateFizzi();

}
