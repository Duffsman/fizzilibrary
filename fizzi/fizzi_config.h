#ifndef fizzi_config_h
#define fizzi_config_h

// This file exists only for telling doxygen about config macros

/** @ingroup core
  Add \#define USE_SYNC at the very top of your sketch (before the \#include statements)
  to activate the sync pulse input.
*/

#define USE_SYNC


/** @ingroup core
  Add \#define USE_ENCODER at the very top of your sketch (before the \#include statements)
  to activate enoder INPUTS on **P2** and **P3**. Access encoder values via **encoder.getPosition() and
  encoder.setPosition()**
*/
#define USE_ENCODER


/** @ingroup core
Add \#define USE_FAST_ADC at the very top of your sketch (before the \#include statements)
to activate the FAST_ADC mode. In this mode you can still use the default analogRead() function.
The reading will be much faster but less precise.
*/

#define USE_FAST_ADC

/** @ingroup core
Add \#define USE_FIZZI_ANALOG at the very top of your sketch (before the \#include statements)
to activate the FIZZI_ANALOG mode. In this mode the default analogRead() function doesn't work anymore, instead use
fizziAnalogRead(). Fizzi analogRead is even faster than FAST_ADC but has only 8 bit resolution.
*/
#define USE_FIZZI_ANALOG

#endif
