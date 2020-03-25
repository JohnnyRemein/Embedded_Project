//******************************************************************************
//
//  Description: This file contains USCI interrupt ISRs
//
//  Johnny Remein
//  11/4/18
//
//  Built with IAR Embedded Workbench Version: (7.12.1)
//******************************************************************************

#include "msp430.h"
#include "functions.h"
#include "macros.h"
#include <string.h>

extern volatile unsigned char Turn;

volatile unsigned int usb_rx_ring_wr;
volatile unsigned int usb_rx_ring_rd;
volatile unsigned int usb_tx_ring_wr;
volatile unsigned int usb_tx_ring_rd;
volatile char USB_Char_Rx[SMALL_RING_SIZE];
volatile char USB_Char_Tx[SMALL_RING_SIZE];
volatile char IoT_Char_Tx[SMALL_RING_SIZE];
volatile char IoT_Char_Rx[LARGE_RING_SIZE];

volatile unsigned int UCA3_index;
volatile unsigned char UCA0_index;
volatile char message_array[MESSAGE_SIZE];
extern volatile unsigned char Turn;
unsigned char char_received;
extern volatile unsigned char Turn; 
volatile unsigned char message_in;
unsigned char mode;
volatile char command_buff[MESSAGE_SIZE];
volatile unsigned int IoT_rx_wr_cnt;
volatile unsigned int command_start;

unsigned int wrchk;




#pragma vector = USCI_A3_VECTOR
__interrupt void USCI_A3_ISR(void){
  
//  unsigned int temp;
  unsigned char temp;
  
  switch(__even_in_range(UCA3IV,V8)){
    case V0:                                                     // Vector 0 - no interrupt
      break;
    case RXIFG:                                                     // Vector 2 – RXIFG

///* Ring Buff    
     temp = UCA3RXBUF;
     IoT_Char_Rx[IoT_rx_wr_cnt] = temp;                            // Put new input character into ring buffer
     Turn = NEW_CHAR;                                                 // Inform main a new char has come in
     UCA0TXBUF = IoT_Char_Rx[IoT_rx_wr_cnt];                            // Send new char out to PC (Only Used for Testing!!)
     if(++IoT_rx_wr_cnt >> SHIFT32){                                          // If wr index >= 32 (>> 5) reset;
       IoT_rx_wr_cnt = RESET;
//       wrchk++;                                                       // Variable to check cycles with case NEW_CHAR
     }
      break;
 //     */

    case TXIFG:                                                     // Vector 4 – TXIFG
      switch(UCA3_index++){
        case CHAR0:
        case CHAR1: //
        case CHAR2: //
        case CHAR3: //
        case CHAR4: //
        case CHAR5: //
        case CHAR6: //
        case CHAR7: //
        case CHAR8: //
        case CHAR9: //
        case CHAR10: //
        case CHAR11: //
        case CHAR12: //
        case CHAR13: //
        case CHAR14: //
          UCA3TXBUF = IoT_Char_Tx[UCA3_index-CNT_CORRECT];
          if(IoT_Char_Tx[UCA3_index] == NULL){
            UCA3_index = CHAR15;
          }
          break;
        case CHAR15:                                                // Vector 0 - no interrupt
          UCA3TXBUF = '\r';
          break;
        case CHAR16:
          UCA3TXBUF = '\n';
        default:
          UCA3_index = RESET;
          UCA3IE &= ~UCTXIE;                                    // Disable TX interrupt
          break;
      } 
      break;

}
}


#pragma vector = USCI_A0_VECTOR 
__interrupt void USCI_A0_ISR(void) {
  
  unsigned int temp0;
  unsigned char command;
  switch(__even_in_range(UCA0IV,V18)) {
    case FALSE: // Vector 0: No interrupts
      break;
    case RXIFG:                                                     // Vector 2 – RXIFG
        
      switch(mode){                                                     // Switch statement for if a command is sent or not
      case REGULAR:                                                     // If not a command, send back out, if "*" sent set to Command mode
        temp0 = UCA0RXBUF;
        
        if(temp0 == CHECK){                                             // If command character sent, put in command mode to check next char
        mode = COMMAND;
        UCA0TXBUF = temp0;
        break;
        }
        
        UCA3TXBUF = temp0;
        break;
        
      case COMMAND:                                                     // Look for which command is sent
        message_in = TRUE;                                              // Set variable identifying a 
        temp0 = UCA0RXBUF;
        UCA0TXBUF = temp0;
        command = temp0;
        
        switch(command){
        case HIGH_BAUD:
          Turn = HIGH_BAUD;
          mode = RESET;
          break;
        case LOW_BAUD:
          Turn = LOW_BAUD;
          mode = RESET;
          break;
        case RESET_IOT:
          Turn = RESET_IOT;
          mode = RESET;
          break;
        case CHECK:
          Turn = CHECK;
          mode = RESET;
          break;
        }
      }
      
    break;
    case TXIFG:                                          // Vector 4: UCTXIFG
      switch(UCA0_index++){
            case CHAR0: 
              if(message_in){                                       // If first time through after receiving a message, add a carriage return
                message_in = FALSE;
                UCA0_index = FALSE;
                UCA0TXBUF = CARRIAGERETURN;
                break;
              }
            case CHAR1: //
            case CHAR2: //
            case CHAR3: //
            case CHAR4: //
            case CHAR5: //
            case CHAR6: //
            case CHAR7: //
            case CHAR8: //
            case CHAR9: //
            case CHAR10:
              UCA0TXBUF = message_array[UCA0_index-CNT_CORRECT];
              if(message_array[UCA0_index-CNT_CORRECT] == NULL){      // If reached the end of a message, skip to CHAR11 case to finish 
                UCA0_index = CHAR11;
              }
              break;
            case CHAR11:
              UCA0TXBUF = LINEFEED;                                     // follow transmit with a line feed
              break;
            case CHAR12:
              UCA0TXBUF = CARRIAGERETURN;                                     // follow transmit with a carriage return
              UCA0IE LO UCTXIE;                                    // Disable TX interrupt
              UCA0_index = RESET;                                   // Reset index counter
              break;
      default: break;
          } 
      break;
    break;
    case V6:                                  // Vector 6: UCSTTIFG
    break;
    case V8:                                  // Vector 8: UCTXCPTIFG
    break;
    default: break;
    }
}



