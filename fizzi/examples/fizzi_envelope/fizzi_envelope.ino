
#include<fizzi.h>
#include<envelope.h>
#include<fizziButton.h>



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
 This example shows how to use the envelope. for demonstration a button has to be connected to P0
*/

#define BUTTON_PIN P0

unsigned int tick = 0;

Envelope env = Envelope();
fizziButton button = fizziButton();


void setup() {
  initFizzi();
  // set values for attack, decay, sustain and release. the duration is measured in samples.
  env.setADSR(400,200,600,3000);
  // setup button, with INPUT_PULLUP we can save an external PULLUP resistor
  pinMode(BUTTON_PIN,INPUT_PULLUP);
  // tell the buttonobject the Pin
  button.attach(BUTTON_PIN);
}



void updateControl(){
  // update button
  button.update();


  //check if the button has been pressed
  if(button.fell()){
    env.noteOn();
  }
  // if the button remains pressed the envelope remains in sustain phase
  // until the button will be released
  if(button.read() == LOW){
    env.hold(true);
  } else {
    env.hold(false);
  }
}

byte magicFormula() {
  int out = ((tick|(tick>>(tick%16)))>>4)& (tick<<2);
  tick++;
  // add the envelope to signal chain
  return env.next(byte(out));
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
