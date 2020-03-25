//******************************************************************************
//
//  Description: This file contains port pin interrupts ISRs
//
//  Johnny Remein
//  10/10/18
//
//  Built with IAR Embedded Workbench Version: (7.12.1)
//******************************************************************************/

#include "msp430.h"
#include "functions.h"
#include "macros.h"
#include <string.h>

extern char display_line[L4][C11];
extern volatile unsigned char update_display;
extern volatile unsigned char display_changed;
volatile unsigned char debounce_button;
extern volatile unsigned char Turn;
extern volatile unsigned char bounced;




// INTERRUPT FOR THE BUTTONS
#pragma vector = PORT5_VECTOR
__interrupt void BUTTON_interrupt(void){
  
  P5IE LO BUTTON1;
  P5IE LO BUTTON2;
  TA0CCTL0 LO CCIE;
  TA0CCTL1 HI CCIE;
  debounce_button = TRUE;
  
  if(bounced){
    bounced = RESET;
     if(P5IFG & BUTTON1){                                    // Button 1 pressed
       Turn = BUTTON1PRESSED;
     }
  
     else if(P5IFG & BUTTON2){                               // Button 2 pressed
       Turn = BUTTON2PRESSED;
     }
  }
  
  

}