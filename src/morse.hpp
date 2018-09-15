#pragma once


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



void print_code(int);
