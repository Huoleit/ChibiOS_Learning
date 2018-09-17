#include "morse.hpp"

using namespace chibios_rt;


void print_code(const morse_code_t& code){
  if(flag_change){
    palSetPad(GPIOA,GPIOA_LED);
  for(int i=0;i<code.length;i++){
    palClearPad(GPIOA,GPIOA_LED);
    if(code.frame[i]==DASH)  chThdSleepMilliseconds(600);
    else if(code.frame[i]==DOT) chThdSleepMilliseconds(200);

    if(!flag_change){
      palSetPad(GPIOA,GPIOA_LED);
      break;
      }

    palSetPad(GPIOA,GPIOA_LED);
    chThdSleepMilliseconds(200);

    if(!flag_change){
      palSetPad(GPIOA,GPIOA_LED);
      break;
      }

    }
  if(flag_change){
    code_state++;
    code_state=code_state%FRAME_LENGTH;
    }
  }
  else chThdSleepMilliseconds(200);


  //palSetPad(GPIOA,GPIOA_LED);
}
