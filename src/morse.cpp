#include "morse.hpp"

using namespace chibios_rt;


void print_code(const morse_code_t& code){
  for(int i=0;i<code.length;i++){

    palSetPad(GPIOA,GPIOA_LED);
    chThdSleepMilliseconds(200);
    if(flag_change) break;

    palClearPad(GPIOA,GPIOA_LED);
    if(code.frame[i]==DASH)  chThdSleepMilliseconds(600);
    else if(code.frame[i]==DOT) chThdSleepMilliseconds(200);
    if(flag_change) break;
  }
  if(flag_change)  flag_change = false;
  else  code_state++;
  palSetPad(GPIOA,GPIOA_LED);
}
