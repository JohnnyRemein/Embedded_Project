//******************************************************************************
//
//  Description: This file contains function definitions
//
//  Johnny Remein
//  11/18/18
//
//  Built with IAR Embedded Workbench Version: (7.12.1)
//******************************************************************************


#include "msp430.h"
#include "functions.h"
#include "macros.h"
#include <string.h>

extern volatile unsigned char display_changed;
extern char display_line[L4][C11];
extern volatile char message_array[MESSAGE_SIZE];
extern volatile char IoT_Char_Tx[SMALL_RING_SIZE];

extern char IP_Addr[SMALL_RING_SIZE];
extern char IP_Addr1[HALF_IP];
extern char IP_Addr2[HALF_IP];
extern volatile unsigned char TA1CCR2_function;
extern volatile unsigned int msecond_count;

extern unsigned char new_action;
extern unsigned char action_type;

unsigned long right_forward_speed;
unsigned long left_forward_speed;
unsigned long slow_right_forward_speed;
unsigned long slow_left_forward_speed;
extern volatile unsigned int general_count;

extern volatile unsigned char Turn;
unsigned char speed;
extern volatile unsigned char move_timer_funct;
extern volatile unsigned char slow_move_timer_funct;
extern volatile unsigned int slow_move_count;


//******************************************************************************
//
// To_Display outputs a character array to the display. It accepts
// a character array (THAT MUST BE 10 CHARACTERS!) and the line to display to.
//
//******************************************************************************
void To_Display(char array[], int line){ 
  for(int i = RESET; i < C11; i++){                     // Fill display_line with spaces
    display_line[line][i] = ' ';
  }

  int length = strlen(array);
  int diff = C10 - length;
  int j = RESET;
  
  if(diff > FALSE){                                     // If string is less than 10, figure out spacing
    for(int i = diff HALF; j < length; i++){
      display_line[line][i] = array[j];
      j++;
    }
  }

  else strncpy(display_line[line], array, C10);         // Otherwise send it straight to display_line
  
  
  display_changed = TRUE;
}


//******************************************************************************
//
// To_PC ouputs a character array to the PC. It accepts a character array (OF NO MORE
// THAN 10 CHARACTERS!).
//
//******************************************************************************
void To_PC(char array[]){
  
  for(int i = RESET; i < MESSAGE_SIZE; i++){                    // Clear message array
    message_array[i] = NULL;
  }
  
  for(int i = RESET; i < strlen(array); i++){                   // Fill message array with array of chars to be sent out
    message_array[i] = array[i];
  }
  
  UCA0TXBUF = LINEFEED;                                         // Initiate Transmission
  UCA0IE HI UCTXIE;
}
           
      
//******************************************************************************
//
//  To_Wifi sends a character array out to the wifi module, it accepts one
//  character array
//
//******************************************************************************
void To_Wifi(char array[]){
  
  for(int i = RESET; i < SMALL_RING_SIZE; i++){                         // Clear Tx Array
    IoT_Char_Tx[i] = RESET;
  }
  
  for(int i = strlen(array); i > RESET; i--){                           // Load message to be sent
    IoT_Char_Tx[i-CNT_CORRECT] = array[i-CNT_CORRECT];
  }
  
  UCA3IE HI UCTXIE;                                                     // Enable Wifi Tx Interrupt
  
}
           
       
//******************************************************************************
//
//  Parse_IP splits the IP Address into two separate characer arrays for sending
//  to the display, it returns nothing and acecpts zero parameters
//
//******************************************************************************
void Parse_IP(void){
  int length = strlen(IP_Addr);                         // Get length of Ip address
  int j = RESET;
  int dot_cnt = RESET;
  
  for(int i = RESET; i < HALF_IP; i++){                 // Clear IP Address arrays
    IP_Addr1[i] = RESET;
    IP_Addr2[i] = RESET;
  }
  
  for(int i = RESET; i < length; i++){                  // Parse the array into two separate arrays
    switch(dot_cnt){
    case NODOT:
    case ONEDOT:
      IP_Addr1[i] = IP_Addr[i];
      if(IP_Addr1[i] == '.') dot_cnt++;
      break;  
      
    case TWOPLUSDOT:                                    // Seen two dots, put everything else in second array
      IP_Addr2[j] = IP_Addr[i];
      j++;
      break;
    }
  }
  
}
    

//******************************************************************************
//
//  Command_Ex controls the movement of the car based on two parameters: a direction
//  and a time interval
//
//******************************************************************************
void Command_Ex(char direction){

  switch(speed){
  case FAST:                                                    // Case for fast movement through the course
    switch(direction){
    case 'F':                                                     // Forward movement execution
      if(RIGHT_REVERSE_SPEED || LEFT_REVERSE_SPEED) break;              // Safety Check
      
      To_Display("FORWARD", L1);
    
      if(right_forward_speed){                                          // If PWMs have been calibrated, set to that
        LEFT_FORWARD_SPEED = left_forward_speed;
        RIGHT_FORWARD_SPEED = right_forward_speed; 
      }
    
      else {                                                            // Otherwise set to max
        RIGHT_FORWARD_SPEED = MAX_SPEED;
        LEFT_FORWARD_SPEED = MAX_SPEED;
      }
    
      break;
           
 
    case 'B':                                                     // Backward movement execution
      if(LEFT_FORWARD_SPEED || RIGHT_FORWARD_SPEED){                    // If going forward, just slow down
        if(LEFT_FORWARD_SPEED > MIN_SPEED && RIGHT_FORWARD_SPEED > MIN_SPEED){
          LEFT_FORWARD_SPEED -= SPEED_CHNG;
          RIGHT_FORWARD_SPEED -= SPEED_CHNG;
        }
        break;
      }
      
      To_Display("BACKWARD", L1);
      LEFT_REVERSE_SPEED = MAX_SPEED;                                   // If stopped, go backwards at max speed
      RIGHT_REVERSE_SPEED = MAX_SPEED;
      
      break;
      
    case 'R':                                                     // Right Turn movement execution      
      if(LEFT_REVERSE_SPEED || RIGHT_REVERSE_SPEED) break;              // Safety Check
      
      To_Display("RIGHT TURN", L1);
      RIGHT_FORWARD_SPEED = WHEEL_OFF;
      LEFT_FORWARD_SPEED = TURN_SPEED;
      
      break;
      
    case 'L':                                                     // Left Turn movement execution     
      if(LEFT_REVERSE_SPEED || RIGHT_REVERSE_SPEED) break;              // Safety Check
      
      To_Display("LEFT TURN", L1);
      LEFT_FORWARD_SPEED = WHEEL_OFF;
      RIGHT_FORWARD_SPEED = TURN_SPEED;
      
      break;
      
    case 'C':                                                     // Case for veering right, by slowing down right  
      if(RIGHT_REVERSE_SPEED || LEFT_REVERSE_SPEED) break;              // Safety Check
      
      if(RIGHT_FORWARD_SPEED > MIN_SPEED && LEFT_FORWARD_SPEED < MAX_SPEED){   
        RIGHT_FORWARD_SPEED -= SPEED_CHNG;
        LEFT_FORWARD_SPEED += SPEED_CHNG;
      }
      
      break;
      
    case 'X':                                                     // Case for veering left, by slowing down left  
      if(RIGHT_REVERSE_SPEED || LEFT_REVERSE_SPEED) break;              // Safety Check
      
      if(LEFT_FORWARD_SPEED > MIN_SPEED && RIGHT_FORWARD_SPEED < MAX_SPEED){
        LEFT_FORWARD_SPEED -= SPEED_CHNG;
        RIGHT_FORWARD_SPEED += SPEED_CHNG;
      }
      
      break;
      
    case 'S':                                                     // Case to stop the car entirely
      To_Display("STOP", L1);
      LEFT_FORWARD_SPEED = WHEEL_OFF;
      LEFT_REVERSE_SPEED = WHEEL_OFF;
      RIGHT_FORWARD_SPEED = WHEEL_OFF;
      RIGHT_REVERSE_SPEED = WHEEL_OFF;
      
      break;
      
    case 'T':                                                     // Case for veering right, and trying to get the fastest straight speed for both motors   
      if(RIGHT_REVERSE_SPEED || LEFT_REVERSE_SPEED) break;              // Safety Check
      
      if(LEFT_FORWARD_SPEED < MAX_SPEED){                       // If left wheel not at max speed yet, speed it up
        LEFT_FORWARD_SPEED += SPEED_CHNG;
      }
      
      else if(RIGHT_FORWARD_SPEED > MIN_SPEED){                 // If left wheel maxed out, slow down right
        RIGHT_FORWARD_SPEED -= SPEED_CHNG;
      }
      
      break;
      
    case 'Q':                                                     // Case for veering left, and trying to get the fastest straight speed for both motors  
      if(RIGHT_REVERSE_SPEED || LEFT_REVERSE_SPEED) break;              // Safety Check
      
      if(RIGHT_FORWARD_SPEED < MAX_SPEED){                      // If right wheel not at max speed yet, speed it up
        RIGHT_FORWARD_SPEED += SPEED_CHNG;
      }
      
      else if(LEFT_FORWARD_SPEED > MIN_SPEED){                  // If left wheel maxed out, slow down right
        LEFT_FORWARD_SPEED -= SPEED_CHNG;
      }
      
      break;
      
    case 'K':                                                     // Case for calibrating speeds for fast forward speed  
      right_forward_speed = RIGHT_FORWARD_SPEED;
      left_forward_speed = LEFT_FORWARD_SPEED;
      
      break;
      
    case 'P':                                                   // Switch to slow movement setting
      speed = SLOW;
      break;
      
    }
   break;
    
    
    
    
   
    
  case SLOW:                                                    // Everything is the same as above, just with slower speeds for finer movement
    switch(direction){
    case 'F':                                                     // Forward movement execution
      if(RIGHT_REVERSE_SPEED || LEFT_REVERSE_SPEED) break;              // Safety Check
      
      To_Display("FORWARD", L1);
    
      if(slow_right_forward_speed){                                          // If PWMs have been calibrated, set to that
        LEFT_FORWARD_SPEED = slow_left_forward_speed;
        RIGHT_FORWARD_SPEED = slow_right_forward_speed; 
      }
    
      else {                                                            // Otherwise set to slow speed
        RIGHT_FORWARD_SPEED = SLOW_SPEED;
        LEFT_FORWARD_SPEED = SLOW_SPEED;
      }
      
    
      break;
           
 
    case 'B':                                                     // Backward movement execution
      if(LEFT_FORWARD_SPEED || RIGHT_FORWARD_SPEED){
        if(LEFT_FORWARD_SPEED > MIN_SPEED && RIGHT_FORWARD_SPEED > MIN_SPEED){
          LEFT_FORWARD_SPEED -= SPEED_CHNG;
          RIGHT_FORWARD_SPEED -= SPEED_CHNG;
        }
        break;
      }
      
      To_Display("BACKWARD", L1);
      LEFT_REVERSE_SPEED = SLOW_SPEED;
      RIGHT_REVERSE_SPEED = SLOW_SPEED;
      
      break;
      
    case 'R':                                                     // Right Turn movement execution
      if(LEFT_REVERSE_SPEED || RIGHT_REVERSE_SPEED) break;              // Safety Check
      
      To_Display("RIGHT TURN", L1);
      RIGHT_FORWARD_SPEED = WHEEL_OFF;
      LEFT_FORWARD_SPEED = S_TURN_SPEED;
      
      break;
      
    case 'L':                                                     // Left Turn movement execution
      if(LEFT_REVERSE_SPEED || RIGHT_REVERSE_SPEED) break;              // Safety Check
      
      To_Display("LEFT TURN", L1);
      LEFT_FORWARD_SPEED = WHEEL_OFF;
      RIGHT_FORWARD_SPEED = S_TURN_SPEED;
      
      break;
      
    case 'C':                                                     // Case for veering right, by slowing down right
      if(RIGHT_REVERSE_SPEED || LEFT_REVERSE_SPEED) break;              // Safety Check
      
      if(RIGHT_FORWARD_SPEED > MIN_SPEED && LEFT_FORWARD_SPEED < MAX_SPEED){
        RIGHT_FORWARD_SPEED -= SPEED_CHNG;
        LEFT_FORWARD_SPEED += SPEED_CHNG;
      }
      
      break;
      
    case 'X':                                                     // Case for veering left, by slowing down left 
      if(RIGHT_REVERSE_SPEED || LEFT_REVERSE_SPEED) break;              // Safety Check
      
      if(LEFT_FORWARD_SPEED > MIN_SPEED && RIGHT_FORWARD_SPEED < MAX_SPEED){
        LEFT_FORWARD_SPEED -= SPEED_CHNG;
        RIGHT_FORWARD_SPEED += SPEED_CHNG;
      }
      
      break;
      
    case 'S':                                                     // Case to stop the car entirely
      To_Display("STOP", L1);
      LEFT_FORWARD_SPEED = WHEEL_OFF;
      LEFT_REVERSE_SPEED = WHEEL_OFF;
      RIGHT_FORWARD_SPEED = WHEEL_OFF;
      RIGHT_REVERSE_SPEED = WHEEL_OFF;
      
      break;
      
    case 'T':                                                     // Case for veering right, by first speeding up motors  
      if(RIGHT_REVERSE_SPEED || LEFT_REVERSE_SPEED) break;              // Safety Check
      
      if(LEFT_FORWARD_SPEED < MAX_SPEED){
        LEFT_FORWARD_SPEED += SPEED_CHNG;
      }
      
      else if(RIGHT_FORWARD_SPEED > MIN_SPEED){
        RIGHT_FORWARD_SPEED -= SPEED_CHNG;
      }
      
      break;
      
    case 'Q':                                                     // Case for veering left, by first speeding up motors   
      if(RIGHT_REVERSE_SPEED || LEFT_REVERSE_SPEED) break;              // Safety Check
      
      if(RIGHT_FORWARD_SPEED < MAX_SPEED){
        RIGHT_FORWARD_SPEED += SPEED_CHNG;
      }
      
      else if(LEFT_FORWARD_SPEED > MIN_SPEED){
        LEFT_FORWARD_SPEED -= SPEED_CHNG;
      }
      
      break;
      
    case 'K':                                                     // Case for calibrating speeds for slow forward speed   
      slow_right_forward_speed = RIGHT_FORWARD_SPEED;
      slow_left_forward_speed = LEFT_FORWARD_SPEED;
      
      break;
      
    case 'I':                                                   // Case to start the Intercept process
      To_Display("INTERCEPT", L1);
      RIGHT_FORWARD_SPEED = INT_SPEED_RIGHT;
      LEFT_FORWARD_SPEED = INT_SPEED_LEFT;
      P3OUT LO IOT_RESET;                                       // Turn off Wifi Module
      slow_move_timer_funct = INTERCEPT;                        // Set slow timer state to Intercept
      slow_move_count = RESET;                                  // Reset timer counter
      TA0CCTL2 HI CCIE;                                         // Enable slow interval timer
      
      break;
      
    case 'E':
      TA1CCTL1 LO CCIE;                                 // Disable fast interval timer
      P8OUT LO IR_LED;                                        // Turn off IR_LED
      ADC12CTL0 LO ADC12ON;                                   // Disable ADC Sampling
      P3OUT LO IOT_RESET;                                       // Turn off Wifi Module
      To_Display("EXITING", L1);
      slow_move_count = RESET;
      slow_move_timer_funct = EXITING;
    
      if(right_forward_speed){                                          // If PWMs have been calibrated, set to that
        LEFT_FORWARD_SPEED = left_forward_speed;
        RIGHT_FORWARD_SPEED = right_forward_speed; 
      }
    
      else {                                                            // Otherwise set to max
        RIGHT_FORWARD_SPEED = MAX_SPEED;
        LEFT_FORWARD_SPEED = MAX_SPEED;
      }
      
      break;
      
    case 'P':                                                           // Set to fast movement setting
      speed = FAST;
      break; 
    }
  break;
  }
}

