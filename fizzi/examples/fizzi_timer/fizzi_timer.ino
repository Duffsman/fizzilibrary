#include<fizzi.h>
#include<fizziTimer.h>

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


connect a LED to P0
*/

/*
This example shows the usage of the fizziTimer.
All timing tasks should make use of the fizziTimer or fizziMetro. delay() doesn't work.
*/

#define LED_PIN P0
unsigned long t= 0;
byte var = 3;

// create new timer object
fizziTimer timer = fizziTimer();
// state variable for Milliseonds
bool ledState = false;




void setup() {
  initFizzi();
  pinMode(LED_PIN,OUTPUT);

}



void updateControl(){
  // when timer is equal to or greater than 500 milliseconds
  if(timer.get() >= 500){
    // reset the timer
   timer.reset();
   // toggle and update led state
   ledState = !ledState;
   digitalWrite(LED_PIN,ledState);
   // compute a new value for var based on t
   var = (t>>5)|(t<<3)&(t<<2);
  }

}

byte magicFormula(){
  t++;
  int out =(t>>2)|(t<<3)*var;
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
