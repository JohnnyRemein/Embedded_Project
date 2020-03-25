//------------------------------------------------------------------------------
//
//  Description: This file contains the Main Routine - "While" Operating System
//
//
//  Johnny Remein
//  9/27/2018
//
//  Built with IAR Embedded Workbench Version: V4.10A/W32 (7.11.2)
//------------------------------------------------------------------------------

//------------------------------------------------------------------------------
#include "msp430.h"
#include "functions.h"
#include "macros.h"
#include <string.h>




// Global Variables
extern char display_line[L4][C11];
extern char *display[L4];
extern volatile unsigned char display_changed;
extern volatile unsigned char update_display;
extern volatile unsigned int update_display_count;
extern volatile unsigned char flick_count;
volatile unsigned char Turn;

extern volatile unsigned int ADC_Thumb;
extern volatile unsigned int ADC_Right_Detector;
extern volatile unsigned int ADC_Left_Detector;
const char* reading;
extern volatile unsigned long msecond_count;

unsigned char button1cnt;
unsigned char button2cnt;
unsigned int AmbLeft;
unsigned int AmbRight;
unsigned int OnLineLeft;
unsigned int OnLineRight;
unsigned int OffLineLeft;
unsigned int OffLineRight;
unsigned int leftThresh;
unsigned int rightThresh;
unsigned int right_val;
unsigned int left_val;
extern volatile unsigned int general_count;

extern volatile char USB_Char_Rx[SMALL_RING_SIZE];
extern volatile char USB_Char_Tx[SMALL_RING_SIZE];
extern volatile unsigned int UCA3_index;

extern volatile unsigned int UCA3_index;
extern volatile char message_array[];
volatile char reset_iot;
char get_IoT_data[] = {"AT+NSTAT=?"};

extern volatile char IoT_Char_Rx[LARGE_RING_SIZE];
extern volatile char IoT_Char_Tx[SMALL_RING_SIZE];
extern volatile unsigned int IoT_rx_wr_cnt;
unsigned int IoT_rx_rd_cnt;
extern volatile unsigned int command_start;
char IP_Addr[SMALL_RING_SIZE];
char IP_Addr1[HALF_IP];
char IP_Addr2[HALF_IP];
char SSID[LARGE_SSID];
char command; 
char command_time[TIMESIZE];
unsigned int rdchk;
unsigned char new_action;
unsigned char action_type;
extern volatile unsigned char slow_move_timer_funct;
extern volatile unsigned int slow_move_count;
extern unsigned long slow_right_forward_speed;
extern unsigned long slow_left_forward_speed;
extern volatile char turn_direction;


void main(void){
//------------------------------------------------------------------------------
// Main Program
// This is the main routine for the program. Execution of code starts here.
// The operating system is Back Ground Fore Ground.
//
//------------------------------------------------------------------------------
// Disable the GPIO power-on default high-impedance mode to activate
// previously configured port settings
  PM5CTL0 LO LOCKLPM5;
  Init_Ports();                        // Initialize Ports
  Init_Clocks();                       // Initialize Clock System
  Init_Conditions();                   // Initialize Variables and Initial Conditions
  Init_Timers();                       // Initialize Timers
  Init_LCD();                          // Initialize LCD
  Init_ADC();                          // Initialize ADC
  Init_Serial();
    
  
  // Local Variables to Main
  unsigned char outer = RESET;
  unsigned char record_cnt = RESET;
  unsigned char calibrated = RESET;
  unsigned char first_command = TRUE;
  unsigned char record_type = RESET;
  unsigned char prev_char = RESET;
  unsigned char new_action = RESET;
  unsigned char action_type = RESET;
  
 
    
//------------------------------------------------------------------------------
// Beginning of the "While" Operating System
//------------------------------------------------------------------------------

  while(ALWAYS) {                      //  main while loop
    

    switch(flick_count){                       // Flick the LED's as an OS checkup
    case LED_FLICK1:
      P1OUT HI GRN_LED;
      P1OUT LO RED_LED;
      break;
      
    case LED_FLICK2:
      P1OUT LO GRN_LED;
      P1OUT HI RED_LED;
      flick_count = RESET;
      break;
        
    default: break;
    }
 
    switch(Turn){                                               // Main state machine
      
    case BUTTON1PRESSED:                                        // If button 1 is pressed, enter calibration sequence
      switch(button1cnt){                                       // switch statement for calibration 
      case PRESSONCE:                                           // Button 1 been pressed once, set up to calibrate to ambient light
        To_Display("AMBIENT", L2); 
        button1cnt++;
        break;
        
      case PRESSTWICE:                                          // Button 1 has been pressed twice, calibrate ambient and set up off line                                         
        To_Display("OFF LINE", L2);
        AmbLeft = ADC_Left_Detector;
        AmbRight = ADC_Right_Detector;
        if(!(P8OUT & IR_LED)) P8OUT HI IR_LED;                  // Turn on IR_LED
        button1cnt++; 
        break;
        
      case PRESSTHIRD:                                           // Button 1 has been pressed thrice, calibrate off line and set up on line
        To_Display("ON LINE", L2);
        OffLineLeft = ADC_Left_Detector;
        OffLineRight = ADC_Right_Detector;
        button1cnt++;
        break;
        
      case PRESSFOURTH:                                           // Button 1 has been pressed four times, calibrate on line and finish calibration
        To_Display("CALIBRATED", L0);
        To_Display("PRESS  FOR", L1);
        To_Display("WIFI", L2);
        OnLineLeft = ADC_Left_Detector;
        OnLineRight = ADC_Right_Detector;
        rightThresh = (OnLineLeft + OffLineLeft)/DIVTWO;        // Calculate averages for right and left detectors
        leftThresh = (OnLineRight + OffLineLeft)/DIVTWO;
        button1cnt++;
        calibrated = TRUE;                                      // set flag to indicate calibration is complete
        TA1CCTL0 LO CCIE;                                       // stop timer that initiates displaying ADC values
        P8OUT LO IR_LED;                                        // Turn off IR_LED
        ADC12CTL0 LO ADC12ON;                                   // Disable ADC Sampling
        break;
        
      case PRESSFIFTH:                                          // Button 1 has been pressed five times, turn on the wifi and get ready to go!
        To_Display("WAITING", L0);
        To_Display("ON COMMAND", L1);
        reset_iot = TRUE;                                       // Set flag and reset timer to bring the IoT module out of reset
        general_count = RESET;
        break; 
      }
                   
      Turn = RESET;
      break;
    
    case BUTTON2PRESSED:                                                    // If button 2 is pressed, IR_LED off and reflect on display
      To_Display("EMITT  OFF", L3);
      P8OUT LO IR_LED;
      Turn = RESET;
      break;
      
    case ADC_TIME_DISPLAY:                                                  // Case for displaying ADC averages or seconds passed
      switch(calibrated){
      case FALSE:
        reading = HEXtoBCD(ADC_Right_Detector);                   // Assign decimal string to reading after hex to decimal conversion
        strcpy(display_line[L0], "RT:   ");                       // Display ADC readings
        strcat(display_line[L0], reading);
      
        reading = HEXtoBCD(ADC_Left_Detector);
        strcpy(display_line[L1], "LT:   ");
        strcat(display_line[L1], reading);
        break;
        
      case TRUE:
        reading = MsecToSec(msecond_count);                       // Sending msecond_count to function to be turned to string and print seconds
        strcpy(display_line[L0], "SEC: ");                
        strcat(display_line[L0], reading);
        break;   
      }

      display_changed = TRUE;
      Turn = RESET;
      break;
      
    case REPLY:                                                 // Commands for communicating via USB, used for testing
      UCA3IE HI UCTXIE;
      Turn = RESET;
      break;
  
    case HIGH_BAUD:
      Init_Serial_UCA3(LOW_BAUD);
      To_Display("GOT H MESS", L1);
      To_PC("High Set");
      Turn = RESET;
      break;
      
    case LOW_BAUD:
      Init_Serial_UCA3(LOWER_BAUD);
      To_Display("GOT L MESS", L1);
      To_PC("Low Set");
      Turn = RESET;
      break;
      
    case RESET_IOT:
      To_Display("RESET  IOT", L1);
      To_PC("Reset IoT");
      P3OUT LO IOT_RESET;
      reset_iot = TRUE;
      general_count = RESET;
      Turn = RESET;
      break;
      
    case CHECK:
      To_Display(" I'm Here ", L1);
      To_PC("Ready");
      TA1CCTL2 HI CCIE;
      Turn = RESET;
      break;
    
    case NEW_CHAR:                                              // Case for recognizing and recording useful data coming in through UCA3RXBUF
      while(IoT_rx_rd_cnt != IoT_rx_wr_cnt){                    // While rd and wr are not the same go read
        switch(outer){                                          // which sequencial character are we looking at?
        case FIRST:                                             // No meaningful character before
          switch(IoT_Char_Rx[IoT_rx_rd_cnt]){                   // What character?
          case 'E':                                     // Waterfall if meaningful character, save character
          case 'd':                                     // for next outer state
          case '*':
            prev_char = IoT_Char_Rx[IoT_rx_rd_cnt];
            outer++;
            break;                                      // break out of IoT_Char_Rx switch
            
          default: break;               
          }
          
          break;                                        // break out of outer switch
          
        case SECOND:                                    // One meaningful character before this
          switch(prev_char){
          case 'd':
            if(IoT_Char_Rx[IoT_rx_rd_cnt] == 'd'){              // If still looks like ip address carry on
              prev_char = IoT_Char_Rx[IoT_rx_rd_cnt];
              outer++;
              break;                                    // early break out of prev_char switch
            }
            outer = RESET;
            break;                                      // break out of prev_char switch
       
          case '*':
            if(IoT_Char_Rx[IoT_rx_rd_cnt] == '1'){              // If still looks like a command carry on
              prev_char = IoT_Char_Rx[IoT_rx_rd_cnt];
              outer++;
              break;                                    // early break out of prev_char switch
            }
            outer = RESET;
            break;                              // break out of prev_char switch
            
          case 'E':
            if(IoT_Char_Rx[IoT_rx_rd_cnt] == 'S'){              // If still looks like a successful network connection carry on
              prev_char = IoT_Char_Rx[IoT_rx_rd_cnt];
              outer++;
              break;                                    // early break out of prev_char switch
            }
            outer = RESET;
            break;                              // break out of prev_char switch
            
          default: 
            outer = RESET;
            break;
          }
          
          break;                                // break out of outer switch
          
        case THIRD:                                     // Two meaningful characters before this       
          switch(prev_char){
          case 'd':                                     
            if(IoT_Char_Rx[IoT_rx_rd_cnt] == 'r'){              // If still looks like Ip address start recording
              prev_char = IoT_Char_Rx[IoT_rx_rd_cnt];
              outer++;
              break;                                    // early break out of prev_char switch
              break;
            }
            outer = RESET;
            break;

          case '1':
            if(IoT_Char_Rx[IoT_rx_rd_cnt] == '9'){              // If still looks like a command carry on
              prev_char = IoT_Char_Rx[IoT_rx_rd_cnt];
              outer++;
              break;
            }
            outer = RESET;
            break;
            
          case 'S':
            if(IoT_Char_Rx[IoT_rx_rd_cnt] == 'S'){              // If still looks like a successful network connection,
              TA1CCR2 = TA1R + TA1CCR2_INTERVAL;               // go ahead and enable timer to get info and connect to TCP 
              TA1CCTL2 HI CCIE;
            }
            outer = RESET;
            break;
            
          default:
            outer = RESET;
            break;
          }
          
          break;                                // break out of outer switch
          
        case FOURTH:
          switch(prev_char){
          case '9':
            if(IoT_Char_Rx[IoT_rx_rd_cnt] == '9'){              // If still looks like a command carry on
              prev_char = IoT_Char_Rx[IoT_rx_rd_cnt];
              outer++;                           
              break;
            }
            outer = RESET;
            break;
            
          case 'r':                                     
            if(IoT_Char_Rx[IoT_rx_rd_cnt] == '='){              // If still looks like Ip address start recording
              record_type = 'I';
              outer = RECORD;                                   // Set outer switch to record state
              record_cnt = RESET;                               // Let Record case know it's the beginning
              break;
            }
            outer = RESET;
            break;
            
          default:
            outer = RESET;
            break;
          }
          
          break;                                // break out of outer switch
          
        case FIFTH:
          switch(prev_char){
          case '9':
            if(IoT_Char_Rx[IoT_rx_rd_cnt] == '1'){              // If still looks like a command start recording command
              record_type = 'C';
              command = RESET;                                  // Clear previous command
              outer++;
              break;
            }
            
            outer = RESET;
            break;
            
          default:
            outer = RESET;
            break;
          }
          
          break;                                // break out of outer switch
          
        case RECORD:
          switch(record_type){
          case 'I':
            if(IoT_Char_Rx[IoT_rx_rd_cnt] & SPACECHK){                  // If not end of IP Address yet
              IP_Addr[record_cnt++] = IoT_Char_Rx[IoT_rx_rd_cnt];       // Increment ip addr index and put address in array
              break;
            }            
            outer = RESET;                                                      // RESETs and set flag for display
            new_action = TRUE;
            action_type = 'I';
            break;
  
          case 'C':
            if(IoT_Char_Rx[IoT_rx_rd_cnt] >> SHIFT64){                          // Record command
              command = IoT_Char_Rx[IoT_rx_rd_cnt];
              break;
            }
            outer = RESET;
            new_action = TRUE;
            action_type = 'C';
            break;
          }
          
          break;                                // break out of outer switch 
        }
               
        if(++IoT_rx_rd_cnt >> SHIFT32){                 // Reset rd counter if at end of ring buffer
          IoT_rx_rd_cnt = RESET;
        }
      }
      
      Turn = RESET;
      break;
    
    case INTERCEPT:
    /*
      right_val = ADC_Right_Detector;           // Take a snapshot
      left_val = ADC_Left_Detector;
      */
      
      if(ADC_Right_Detector < (OnLineRight - FUDGE) && ADC_Left_Detector < (OnLineLeft - FUDGE)){   // If no black line yet, just keep going
        Turn = RESET;
        break;
      }
            
      LEFT_FORWARD_SPEED = WHEEL_OFF;                 // If you see a black line, halt!!
      RIGHT_FORWARD_SPEED = WHEEL_OFF;
      LEFT_REVERSE_SPEED = WHEEL_OFF;
      RIGHT_REVERSE_SPEED = WHEEL_OFF;
      
      TA1CCTL1 LO CCIE;
      To_Display("WAITING", L1);
      turn_direction = LEFT;
      slow_move_timer_funct = WAITING;                     // Set case for slow interval timer 
      slow_move_count = RESET; 
      
      Turn = RESET;
      break;
      
    case FOLLOWING:
      LEFT_FORWARD_SPEED = SLOW_SPEED;
      RIGHT_FORWARD_SPEED = SLOW_SPEED;
      
      if(ADC_Right_Detector < rightThresh){                         // If veering left
        RIGHT_FORWARD_SPEED = WHEEL_OFF;
      }

      else if(ADC_Left_Detector > leftThresh){                 // If veering right
        LEFT_FORWARD_SPEED = WHEEL_OFF;
      }
      
      else {                                                  // Anything else
        RIGHT_FORWARD_SPEED = SLOW_SPEED;
        LEFT_FORWARD_SPEED = SLOW_SPEED;
      }
      Turn = RESET;
      break;
      
    default: break;
    }
    
    
    
    if(new_action){                                               // Update display or make a movement if needed
      
      switch(action_type){
      case 'I':                                                 // Case for displaying network info
        Parse_IP();
        To_Display(IP_Addr1, L2);
        To_Display(IP_Addr2, L3);
        break;
        
      case 'C':                                                 // Case for displaying command info and executing commands
        if(first_command){                                      // If first command, start T0A1 to initiate displaying the second counter
          first_command = RESET;
          msecond_count = RESET;
          TA1CCR0 = TA1R + TA1CCR0_INTERVAL;                   
          TA1CCTL0 HI CCIE;
        }
        Command_Ex(command);                                    // Send command to command function
        break;
        
      default: break;
      }
      
      new_action = RESET;
      action_type = RESET;
    }
  }     


//------------------------------------------------------------------------------

}



