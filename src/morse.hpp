#ifndef _MORSE_H_
#define _MORSE_H_

#include "ch.hpp"

#include "ch.h"
#include "hal.h"

#include "shell.h"
#include "chprintf.h"

#include "morse.hpp"

#define FRAME_LENGTH  8
typedef enum{
  B_UP = 0,
  B_DOWN,
  B_HOLD

}button_state_t;

typedef enum{
  DASH = 0,
  DOT,
  NONE
}code_t;

typedef struct{
  uint8_t length;
  code_t frame[4];

}morse_code_t;



extern volatile bool flag_change;
extern volatile int code_state;


void print_code(const morse_code_t& code);

#endif /* end of include guard: _MORSE_H_ */
