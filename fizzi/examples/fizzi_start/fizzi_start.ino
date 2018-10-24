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
*/

// the very basic structure for a fizzi sketch


/* the counter t. depending on the datatype it overflows more or less often
e.g.:
unsigned long -> 32 bit -> 2^32 = 4.294.967.296 -> divide by 8000 (samplerate) -> divide by 3600 (seconds per hour) -> ca. 149 h
so every 149 hours the counter will overflow

*/

unsigned long t= 0;



void setup() {
  // start fizzi
  initFizzi();

}



void updateControl(){
  // here goes the code
}

// this is where the magic happens
byte magicFormula(){
  // increment t
  t++;
  // compute a sample
  int out =(t>>2)|(t<<3);
  return byte(out);
}



byte defaultOut() {

  return magicFormula();
}



void loop() {
  updateFizzi();
  // don't add anything here

}
