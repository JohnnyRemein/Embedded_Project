//******************************************************************************
//
//  Description: This file contains timer interrupt ISRs
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

volatile unsigned char flick_count;
volatile unsigned char update_count; 
volatile unsigned char bounce_count;
extern volatile unsigned char update_display;
extern volatile unsigned char debounce_button;
volatile unsigned char bounced;
volatile unsigned int general_count;
volatile unsigned long msecond_count;
volatile unsigned int slow_move_count;
extern volatile char reset_iot;
extern volatile unsigned char Turn;
char Proj9[] = {"IP Address"};
extern char display_line[L4][C11];

unsigned char first_time = TRUE;
unsigned char ADC_time_cnt;
volatile unsigned int iot_count;
volatile unsigned char move_timer_funct;
volatile unsigned char slow_move_timer_funct;
unsigned char start_sampling = TRUE;
unsigned char turning = TRUE;
unsigned char first_turn = TRUE;

extern volatile unsigned int ADC_Right_Detector;
extern volatile unsigned int ADC_Left_Detector;
extern unsigned int leftThresh;
extern unsigned int rightThresh;
volatile char turn_direction;


// Interupt for timer A0
#pragma vector = TIMER0_A0_VECTOR
__interrupt void TIMER_A0_ISR(void){
  
  flick_count++;   
  general_count++;
  update_count++;
  
  if(update_count >= DISPLAYTIME){                              // Counter for updating update_display
    update_display = TRUE;
    Display_Update(FALSE, FALSE, FALSE, FALSE);
    update_count = RESET;
  }
  
  if(reset_iot && general_count >= TIME_IN_RESET){              // Counter for reseting the iot module
    P3OUT HI IOT_RESET;
    reset_iot = RESET;
  }
   
  TA0CCR0 += TA0CCR0_INTERVAL;
}


// TimerA0 1-3, Overflow Interrupt Vector (TAIV) handler
#pragma vector = TIMER0_A1_VECTOR
__interrupt void TIMER0_A1_ISR(void){
  

switch(__even_in_range(TA0IV,OVERFLOW)){
   case RESET: break;                                  // No interrupt
   
   case CCR1S:                                         // CCR1 Debounce interrupt
     if(debounce_button){
       bounce_count++;                             // increment bounce counter
       
       if(bounce_count >= BOUNCETIME){                     // 60 intervals of 5ms seconds to get 300ms
         bounced = TRUE;
         bounce_count = RESET;
         debounce_button = RESET;
         P5IE HI BUTTON1;
         P5IE HI BUTTON2;
         P5IFG LO BUTTON1;
         P5IFG LO BUTTON2;
         TA0CCTL0 HI CCIE;                              // Re-Enable CCR0 for TA0
       }
     }
     TA0CCR1 += TA0CCR1_INTERVAL;                  // Add Offset to TACCR1
     break;
   
   case CCR2S:                                         // CCR2 Used for the movement operations that do not require fast intervals
     slow_move_count++;
     
     switch(slow_move_timer_funct){
       
     case INTERCEPT:
       if(slow_move_count >= IR_TIME){              // After about 2.5s has passed, start looking for black line
         switch(start_sampling){                    // If first time through, start sampling
         case TURN_IR_ON:
           P8OUT HI IR_LED;                     // Turn on IR_LED
           ADC12CTL0 HI ADC12ON;                // Start ADC Sampling
           start_sampling++;
           move_timer_funct = INTERCEPT;
           break;
         case IR_ON:
           TA1CCTL1 HI CCIE;                    // Enable fast interval timer
           start_sampling++;
           break;
         default: break;
         }
       }
       break;
       
     case WAITING:
       if(slow_move_count >= WAITTIME){         // If about 1s has passed, stop waiting
         if(turning){                           // If first time through, need to turn
           To_Display("TURNING", L1);
           slow_move_count = RESET;
           slow_move_timer_funct = TURNING;
           turning = RESET;
         }
         
         else {                                 // If second time through, initiate following
           To_Display("FOLLOWING", L1);
           slow_move_count = RESET;
           move_timer_funct = FOLLOWING;
           slow_move_timer_funct = FOLLOWING;
           TA1CCTL1 HI CCIE;                    // Enable fast interval timer
         }
       }
       break;
       
     case TURNING:
       if(first_turn){
         switch(turn_direction){
         case RIGHT:
           RIGHT_REVERSE_SPEED = S_TURN_SPEED;            // If first time through, start turning
           LEFT_FORWARD_SPEED = S_TURN_SPEED;
           first_turn = RESET;
           break;
           
         case LEFT:
           RIGHT_FORWARD_SPEED = S_TURN_SPEED;            // If first time through, start turning
           LEFT_REVERSE_SPEED = S_TURN_SPEED;
           first_turn = RESET;
           break;
         }
       }
       
       else if(ADC_Right_Detector > rightThresh){                  // If right detector sees line, stop movement and wait
         LEFT_FORWARD_SPEED = WHEEL_OFF;
         RIGHT_FORWARD_SPEED = WHEEL_OFF;
         LEFT_REVERSE_SPEED = WHEEL_OFF;
         RIGHT_REVERSE_SPEED = WHEEL_OFF;
         first_turn = TRUE;                             // Set flag for Following case
         slow_move_count = RESET;
         slow_move_timer_funct = WAITING;           
       }
       break;
       
     case FOLLOWING:
       if((slow_move_count >= RESET_IOT_TIME) & first_turn){
         reset_iot = TRUE;
         general_count = RESET;
         first_turn = RESET;
       }
       break;
       
     case EXITING:
       if(slow_move_count >= EXIT_TIME){
         LEFT_FORWARD_SPEED = WHEEL_OFF;                 // Turn off all motors and display done!
         RIGHT_FORWARD_SPEED = WHEEL_OFF;
         LEFT_REVERSE_SPEED = WHEEL_OFF;
         RIGHT_REVERSE_SPEED = WHEEL_OFF;
         To_Display("DONE!!", L1);
         lcd_BIG_mid();
         TA1CCTL0 LO CCIE;         
       }
       break;
     }
     
     TA0CCR2 += TA0CCR2_INTERVAL;                  // Add Offset to TACCR2*/
     break;           
   
   case OVERFLOW:                                        // overflow
     break;
     
default: break;
}

}

// Timer interrupt for averaging and displaying ADC readings
#pragma vector = TIMER1_A0_VECTOR
__interrupt void TIMER1_A0_ISR(void){
  
  ADC_time_cnt++;
  msecond_count++;
  
  if(ADC_time_cnt >= DISPLAYTIME){
    Turn = ADC_TIME_DISPLAY;                           // Display ADC Values or time every 200 ms when enabled
    ADC_time_cnt = RESET;
  }
  
  TA1CCR0 += TA1CCR0_INTERVAL; 
}


// Timer interrupt for watching the line
#pragma vector = TIMER1_A1_VECTOR
__interrupt void TIMER1_A1_ISR(void){
  
  switch(__even_in_range(TA1IV,OVERFLOW)){
   case RESET: break;                                  // No interrupt
   
   case CCR1S:                                         // CCR1 Car movement timer for autonomous movement requiring lots of intervals
     
     switch(move_timer_funct){
     case INTERCEPT:
       Turn = INTERCEPT;
       break;
              
     case FOLLOWING:                                    // If following, start following the black line
       Turn = FOLLOWING;
       break;   
     }

     TA1CCR1 += TA1CCR1_INTERVAL;                  // Add Offset to TA1CCR1 to interrupt every TA1CCR1_INTERVAL
     break;
   
   case CCR2S:                                         // CCR2: timer for getting wifi info and connecting/reconnecting to TCP
                                     
       iot_count++;   
     
       if(first_time & (iot_count >= CONNECT_TIME)){
         first_time = FALSE;
         To_Wifi("at+nstat=?");
       }
     
       else if(iot_count >= TCP_TIME){                   // (10 increments per second) if set time has passed, do something
         first_time = TRUE;
         iot_count = RESET;
         To_Wifi("at+nstcp=1991,1");
         TA1CCTL2 LO CCIE;
         break;
       }
        
     TA1CCR2 += TA1CCR2_INTERVAL;
     break;           
   
   case OVERFLOW:                                        // overflow
     break;
     
   default: break;
   
   
  }
}