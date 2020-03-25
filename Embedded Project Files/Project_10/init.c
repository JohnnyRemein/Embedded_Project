//------------------------------------------------------------------------------
//
//  Description: This file is for initializing the display text
//
//
//  Jonathan Remein
//  9/23/18
//  Built with IAR Embedded Workbench Version: (7.12.1)
//------------------------------------------------------------------------------


#include "msp430.h"
#include "functions.h"
#include "macros.h"
#include <string.h>

// Globals

extern volatile unsigned char update_display;
extern volatile unsigned int update_display_count;
extern char display_line[L4][C11];
extern char *display[L4];



void Init_Conditions(void){
//------------------------------------------------------------------------------

  Clear_Display();

// Interrupts are disabled by default, enable them.
  enable_interrupts();
//------------------------------------------------------------------------------
}

void Clear_Display(void){
    for(int i=LOW;i<C11;i++){
        display_line[L0][i] = RESET_STATE;
        display_line[L1][i] = RESET_STATE;
        display_line[L2][i] = RESET_STATE;
        display_line[L3][i] = RESET_STATE;
  }
  
  display_line[L0][C10] = RESET;
  display_line[L1][C10] = RESET;
  display_line[L2][C10] = RESET;
  display_line[L3][C10] = RESET;

  display[L0] = &display_line[L0][C0];
  display[L1] = &display_line[L1][C0];
  display[L2] = &display_line[L2][C0];
  display[L3] = &display_line[L3][C0];
  update_display = RESET;
  update_display_count = RESET;
}