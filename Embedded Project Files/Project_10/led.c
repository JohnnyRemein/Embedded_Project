//------------------------------------------------------------------------------
//
//  Description: This file is for turning on the LED's
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


void Init_LEDs(void){
//------------------------------------------------------------------------------
// LED Configurations
//------------------------------------------------------------------------------
// Turns on both LEDs
  P1OUT LO RED_LED;
  P1OUT LO GRN_LED;
//------------------------------------------------------------------------------
}