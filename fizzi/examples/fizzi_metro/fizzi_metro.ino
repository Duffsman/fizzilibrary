#include<fizzi.h>
#include<fizziMetro.h>


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
This example shows the usage of the fizziMetro by blinking a LED on pin P0.
All timing tasks should make use of the fizziTimer or fizziMetro. delay() doesn't work.
*/

#define LED_PIN P0
unsigned long t= 0;
// create fizziMetro object
fizziMetro metro = fizziMetro();
bool ledState = false;




void setup() {
  initFizzi();
  pinMode(LED_PIN,OUTPUT);

  // set the interval to 500 ms
  metro.setIinterval(500);

}



void updateControl(){
  // update metro
  if(metro.get()){
    // if interval has passed the led will be toggled
   ledState = !ledState;
   digitalWrite(LED_PIN,ledState);
  }

}

byte magicFormula(){
  t++;
  int out =(t>>2)|(t<<3);
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
