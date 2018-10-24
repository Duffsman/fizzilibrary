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


#endif
