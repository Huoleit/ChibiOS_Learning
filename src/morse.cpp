#include "morse.hpp"

void print_code(int code_state_f){
  for(int i=0;i<champion[code_state_f].length;i++){

    palSetPad(GPIOA,GPIOA_LED);
    chThdSleepMilliseconds(200);

    palClearPad(GPIOA,GPIOA_LED);
    if(champion[code_state_f].frame[i]==DASH)  chThdSleepMilliseconds(600);
    else if(champion[code_state_f].frame[i]==DOT) chThdSleepMilliseconds(200);
    if(flag_change) break;
  }
  if(flag_change)  flag_change = false;
  else  code_state++;
  palSetPad(GPIOA,GPIOA_LED);
}
