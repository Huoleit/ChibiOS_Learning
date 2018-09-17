/*
    ChibiOS - Copyright (C) 2006..2018 Giovanni Di Sirio

    Licensed under the Apache License, Version 2.0 (the "License");
    you may not use this file except in compliance with the License.
    You may obtain a copy of the License at

        http://www.apache.org/licenses/LICENSE-2.0

    Unless required by applicable law or agreed to in writing, software
    distributed under the License is distributed on an "AS IS" BASIS,
    WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
    See the License for the specific language governing permissions and
    limitations under the License.
*/

/**
 * @brief This file is based on the MAPLE MINI example from ChibiOS
 *
 * @file main.cpp
 * @author Alex Au
 * @date 2018-09-11
 */

#include "ch.hpp"

#include "ch.h"
#include "hal.h"

#include "shell.h"
#include "chprintf.h"

#include "morse.hpp"

using namespace chibios_rt;

/*
 * Application entry point.


 */
 morse_code_t champion[FRAME_LENGTH]={
  {4,{DASH,DOT,DASH,DOT}},
  {4,{DOT,DOT,DOT,DOT}},
  {2,{DOT,DASH,NONE,NONE}},
  {2,{DASH,DASH,NONE,NONE}},
  {4,{DOT,DASH,DASH,DOT}},
  {2,{DOT,DOT,NONE,NONE}},
  {3,{DASH,DASH,DASH,NONE}},
  {2,{DASH,DOT,NONE,NONE}}
 };

volatile int code_state = 0;
volatile bool flag_change = true;     //标志是否可以亮灯  true为可以亮灯 false 为不可以亮灯
//extern morse_code_t champion[];

static THD_WORKING_AREA(button_thread_wa,128);
static THD_FUNCTION(button_function,p){
  button_state_t morse_button = B_UP;
  systime_t gap_time;

  while(true){
    if(morse_button==B_UP&&(!palReadPad(GPIOA,GPIOA_BUTTON)))  morse_button = B_DOWN;

    if(morse_button==B_DOWN&&palReadPad(GPIOA,GPIOA_BUTTON)){
        morse_button = B_HOLD;   //进入开关检测时间
        flag_change = false;
        code_state++;
        code_state = code_state%FRAME_LENGTH;   //执行状态标记

        gap_time = chibios_rt::System::getTime()+TIME_MS2I(300);  //松开butto后多久可以进行亮灯
      }
    if(morse_button==B_HOLD){
      if(chibios_rt::System::getTime() > gap_time){
        flag_change = true;

        morse_button=B_UP;
      }
      if(!palReadPad(GPIOA,GPIOA_BUTTON))  morse_button=B_DOWN;
    }

    chThdSleepMilliseconds(70);   //极其小的挂起保证开关检测的准确性
  }
}

//LED
static THD_WORKING_AREA(led_thread_wa,128);
static THD_FUNCTION(led_function,p){


  while(true){
    print_code(champion[code_state]);
  }
}
int main(void)
{

  /*
   * System initializations.
   * - HAL initialization, this also initializes the configured device drivers
   *   and performs the board-specific initializations.
   * - Kernel initialization, the main() function becomes a thread and the
   *   RTOS is active.
   */
  halInit();
  chSysInit();
/////////////////////////////////*******************

  while(palReadPad(GPIOA,GPIOA_BUTTON));
  while(!palReadPad(GPIOA,GPIOA_BUTTON));
  //开机按键启动
  chThdCreateStatic(button_thread_wa,sizeof(button_thread_wa),NORMALPRIO,button_function,NULL);
  chThdCreateStatic(led_thread_wa,sizeof(led_thread_wa),NORMALPRIO,led_function,NULL);
  //volatile int i =0;
  /*
   * Normal main() thread activity
   */
  while (true)
  {
    //i++;
    systime_t startT = chibios_rt::System::getTime();

    //do something..

    chibios_rt::BaseThread::sleepUntil(startT + TIME_MS2I(500));
    //chThdSleepMilliseconds(500); <- any difference using this?
  }
}
