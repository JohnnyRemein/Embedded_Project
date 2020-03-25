//******************************************************************************
//
//  Description: This file contains the functions for converting computer time 
//               and values to be sent to the Display
//
//  Johnny Remein
//  10/10/18
//
//  Built with IAR Embedded Workbench Version: (7.12.1)
//******************************************************************************

#include "msp430.h"
#include "functions.h"
#include "macros.h"
#include <string.h>

char adc_char[] = {'0','0','0','0', NULL};
char sec_time[] = {'0','0','0','.','0', NULL};



//------------------------------------------------------------------------------
//******************************************************************************
// Hex to BCD Conversion
// Convert a Hex number to a BCD for display on an LCD or monitor
//
//------------------------------------------------------------------------------
char* HEXtoBCD(int hex_value){
    int value = RESET;
    adc_char[THOUSPLACE] = '0';
    
    while (hex_value > THOUSLESS){
      hex_value = hex_value - THOUS;
      value = value + PLUSONE;
    }
    adc_char[THOUSPLACE] = ASCIIZ + value;
    
    value = RESET;
    while (hex_value > HUNDSLESS){
      hex_value = hex_value - HUNDS;
      value = value + PLUSONE;
    }
    adc_char[HUNDSPLACE] = ASCIIZ + value;
    
    value = RESET;
    
    while (hex_value > TENSLESS){
      hex_value = hex_value - TENS;
      value = value + PLUSONE;
    }
    adc_char[TENSPLACE] = ASCIIZ + value;
    
    adc_char[ONESPLACE] = ASCIIZ + hex_value;
    
    return &adc_char[THOUSPLACE];
}




//******************************************************************************
// Msec to sec conversion for display
// Convert a counter incremented ever .1s to seconds
//
//------------------------------------------------------------------------------

char* MsecToSec(int msec_hunds){
  int value = RESET;
  
  while (msec_hunds > THOUSLESS){
      msec_hunds = msec_hunds - THOUS;
      value = value + PLUSONE;
    }
    sec_time[THOUSPLACE] = ASCIIZ + value;
    
    value = RESET;
    while (msec_hunds > HUNDSLESS){
      msec_hunds = msec_hunds - HUNDS;
      value = value + PLUSONE;
    }
    sec_time[HUNDSPLACE] = ASCIIZ + value;
    
    value = RESET;
    
    while (msec_hunds > TENSLESS){
      msec_hunds = msec_hunds - TENS;
      value = value + PLUSONE;
    }
    sec_time[TENSPLACE] = ASCIIZ + value;
    
    sec_time[TENTHSPLACE] = ASCIIZ + msec_hunds;
    
    return &sec_time[THOUSPLACE];
  
}

