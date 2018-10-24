#ifndef fizzi_boards_h
#define fizzi_boards_h

#define cbi(sfr, bit) (_SFR_BYTE(sfr) &= ~_BV(bit)) // clear bit
#define sbi(sfr, bit) (_SFR_BYTE(sfr) |= _BV(bit)) // set bit


#if defined(__AVR_ATtiny84__)||defined(__AVR_ATtiny44__)|| defined(__AVR_ATtiny24__)
#define P0 5  // analog
#define P1 4  // analog
#define P2 3  // analog
#define P3 2 // analog
#define P4 1 // analog
#define P5 0 // analog
#define POUT 8  // 'P6'

#ifdef USE_SYNC
#define PSYNC 9
#else
#define P7 9 // SYNC INPUT PIN
#endif

#define P8 10 // no analog
#define P9 7 // analog
#define P10 6 // analog

#define ENCODER_PINA P2
#define ENCODER_PINB P3
#define ENCODER_INTERRUPT PCINT0_vect
#define ENCODER_PIN_REG PINA
#define ENCODER_REG_MASK 0x0C
#define ENCODER_L_SHIFT_A 2
#define ENCODER_L_SHIFT_B 3

#define SYNC_INTERRUPT PCINT1_vect
#define SYNC_PIN_REG PINB
#define SYNC_L_SHIFT 1
#define TIMER_INTERRUT TIM1_COMPA_vect
#define OUTPUT_REG OCR0A

void setupTimer(){
  cli();
  // calibrate internal Oscilator
  //OSCCAL = 111;
  /*******************************/
  /*timer 1 -> sampleratetimer   */
  /*******************************/
  //stop and reset timer
  TCCR1B = 0x00;
  TCCR1A = 0x00;
  TCCR1C = 0x00;
  TCNT1H = 0x00;
  TCNT1L = 0x00;
  TIMSK1 = 0x00;
  // enable CTC Mode with OCR1A as Top
  //cbi(TCCR1A, WGM10);
  //cbi(TCCR1A, WGM11);
  sbi(TCCR1B, WGM12);
  //cbi(TCCR1B, WGM13);

  //enable interrupt on output compare A match
  sbi(TIMSK1, OCIE1A);

  // set prescaler to 1
  sbi(TCCR1B, CS10);
  cbi(TCCR1B, CS11);
  cbi(TCCR1B, CS12);
  // set compare value
  // Fout = F_CPU/(2*prescaler*(1+compareValue))
  //768 + 231 = 999 -> eigentlich 16kHz ??!
  OCR1AH =  0x03;
  OCR1AL = 0xE7;
  // 256 + 243 = 499 -> 8 kHz
  //OCR1AH = 0x01;
  //OCR1AL = 0xF3;

  /****************************************************/
  /*timer 0 -> PWM output on Pin PB2 (8) on ATTINY 84 */
  /****************************************************/

  //stop and reset timer
  TCCR0A = 0x00;
  TCCR0B = 0x00;
  TCNT0 = 0x00;
  // clear output on compare match
  sbi(TCCR0A, COM0A1);
  cbi(TCCR0A, COM0A0);


  // enable FastPWM with 0xFF as top
  sbi(TCCR0A, WGM00);
  sbi(TCCR0A, WGM01);
  cbi(TCCR0B, WGM02);

  //set prescaler to 1 -> Fout = 31.250 Hz
  sbi(TCCR0B, CS00);

  sei();

}

void setupSync(){
  cli();
  // enable interrupt for sync input
  sbi(GIMSK, PCIE1); // enable pinChangeInterrupt on pins 8...10
  sbi(PCMSK1, PCINT9); // enable interrupt on pin 9
  sei();
}

void setupEncoder() {
  cli();
  // enable interrupt for sync input
  sbi(GIMSK, PCIE0); // enable pinChangeInterrupt on pins 0...7
  sbi(PCMSK0, PCINT2); // enable interrupt on pin 2 // fizzi P3
  sbi(PCMSK0, PCINT3); // enable interrupt on pin 3 // fizzi P2
  sei();
}

#elif defined(__AVR_ATtiny261__)||defined(__AVR_ATtiny461__)||defined(__AVR_ATtiny861__)


#ifdef USE_ENCODER
uint8_t _oldStateEnc = 0;
#endif

#define P0 0  //PA0 analog
#define P1 1  //PA1 analog
#define P2 2  //PA2 analog
#define P3 10 //PA4 analog
#define P4 11 //PA5 analog
#define P5 12 // PA6 analog
#define P6 13  // PA7 analog
#define P7 3  // PB6 analog
#define P8 14 //PA3
#define P9 9 // PB0
#define P10 7 // PB2
#define POUT 8  // PB1

// extra analog shizzle -.-
#define A_P0 A0
#define A_P1 A1
#define A_P2 A2
#define A_P3 A3
#define A_P4 A4
#define A_P5 A5
#define A_P6 A6
#define A_P7 A9

#ifdef USE_SYNC
#define PSYNC 6 // PB3
#else
#define P12 6
#endif

#define ENCODER_PINA P2
#define ENCODER_PINB P3
#define ENCODER_INTERRUPT PCINT_vect
#define ENCODER_PIN_REG PINA
#define ENCODER_REG_MASK 0x14
#define ENCODER_L_SHIFT_A 2
#define ENCODER_L_SHIFT_B 4


#define SYNC_INTERRUPT PCINT_vect
#define SYNC_PIN_REG PINB
#define SYNC_L_SHIFT 3
#define TIMER_INTERRUT TIMER0_COMPA_vect
#define OUTPUT_REG OCR1A




void setupTimer(){
  cli();
  // SAMPLERATE TIMER 0

  TCCR0A = 0x00;
  TCCR0B = 0x00;
  TCNT0L = 0x00;

  //enable ctc mode
  sbi(TCCR0A, CTC0);
  // set prescaler to 8
  sbi(TCCR0B, CS01);
  // sbi(TCCR0A, CS00);
  // Fout = F_CPU / (2*prescaler*(OCR0A+1))
  // OCR0A = 130;
  OCR0A = 249; // F = 8000 Hz
  //OCR0A = 56;

  // enable compareMatch Interrupt
  sbi(TIMSK, OCIE0A);

  // PWM TIMER 1
  TCCR1A = 0x00;
  TCCR1B = 0x00;
  TCCR1C = 0x00;
  TCCR1D = 0x00;

  // enable fast PWM on OC1A (pin 8 / PB1)
  sbi(TCCR1A, PWM1A);
  sbi(TCCR1A, COM1A1);
  // set prescaler to 1
  sbi(TCCR1B, CS10);
  //sbi(TCCR1B, CS12);
  // enable PLL
  sbi(PLLCSR, PLLE);
  // wait 100 µs for the clock to stabilize
  // lets asume counting up by one takes one colck cycle, at F_CPU = 20 Mhz
  // so with every count 0,5 µs passes, let it xount a bit further to be sure 100µs have passed
  uint16_t waitCount = 0;
  while (waitCount < 300) {
    waitCount++;
  }
  // wait unitl PLL is locked
  while (!bit_is_set(PLLCSR, PLOCK));
  // enable clock
  sbi(PLLCSR, PCKE);
  OCR1C = 255;

  sei();
}

void setupSync(){
  cli();
  // SYNC
  // enable interrupt for sync input
  sbi(GIMSK, PCIE0); // enable pinChangeInterrupt on pins 8...11
  PCMSK1 = 0x00;
  sbi(PCMSK1, PCINT11); // enable interrupt on pin 6 / PB3
  //sbi(PCMSK1,1); // PCINT8

  sei();
}

void setupEncoder() {
  cli();
  sbi(GIMSK, PCIE1); // enable pinChangeInterrupt on pins 0...7
  PCMSK0 = 0x00;
  sbi(PCMSK0,PCINT2);
  sbi(PCMSK0,PCINT4);
  sei();
}


#else
#error "microcontroller not supported"
#endif


#endif
