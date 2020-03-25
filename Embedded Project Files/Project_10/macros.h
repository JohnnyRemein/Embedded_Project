//******************************************************************************
//
//  Description: This file contains macro definitions
//
//  Johnny Remein
//  Sep 2018
//  Built with IAR Embedded Workbench Version: (7.12.1)
//******************************************************************************

// Port MACROS


// Port 1 Pins
#define RED_LED              (0x01) // RED LED
#define GRN_LED              (0x02) // GREEN LED
#define V_THUMB              (0X04) // ADC FOR THUMB WHEEL
#define TEST_PROBE           (0X08) // GP I/O PIN TO CHECK CODE OPERATION
#define V_DETECT_R           (0X10) // ADC FOR RIGHT DETECTOR
#define V_DETECT_L           (0X20) // ADC FOR LEFT DETECTOR
#define SD_UCB0SIMO          (0X40) // SPI MODE - SLAVE IN/MASTER OUT FOR SD CARD
#define SD_UCB0SOMI          (0X80) // SPI MODE - SLAVE OUT/MASTER IN FOR SD CARD


// Port 2 Pins
#define UCA0TXD              (0X01) // SERIAL PORT TRANSMIT TO PC
#define UCA0RXD              (0X02) // SERIAL PORT RECEIVE FROM PC
#define SD_SPICLK            (0X04) // SD CARD SPI BUS CLOCK
#define P2_3                 (0X08) // UNUSED
#define P2_4                 (0X10) // UNUSED
#define UCA1TXD              (0X20) // SERIAL PORT TRANSMIT TO ?
#define UCA1RXD              (0X40) // SERIAL PORT RECEIVE FROM ?
#define P2_7                 (0X80) // UNUSED


// Port 3 Pins
#define IOT_RESET            (0X01) // RESET
#define IOT_PROG_MODE        (0X02) // IOT_PROG_MODE
#define IOT_LINK             (0X04) // IOT_LINK
#define IOT_PROG_SEL         (0X08) // IOT_PROG_SEL
#define L_REVERSE            (0X10) // LEFT REVERSE
#define L_FORWARD            (0X20) // LEFT FORWARD
#define R_REVERSE            (0X40) // RIGHT REVERSE
#define R_FORWARD            (0X80) // RIGHT FORWARD


// Port 4 Pins
#define SD_CS                (0X01) // SD CARD CHIP SELECT
#define J4_31                (0X02) // UNUSED
#define J4_32                (0X04) // UNUSED
#define J4_33                (0X08) // UNUSED
#define UCB1_CS_LCD          (0X10) // SPI BUS CHIP SELECT LCD
#define P4_5                 (0X20) // UNUSED
#define P4_6                 (0X40) // UNUSED
#define JS_29                (0X80) // UNUSED


// Port 5 pins
#define SPI_UCB1SIMO         (0X01) // SPI BUS SLAVE IN/MASTER OUT
#define SPI_UCB1SOMI         (0X02) // SPI BUS SLAVE OUT/MASTER IN
#define SPI_UCB1CLK          (0X04) // SPI BUS CLOCK
#define RESET_LCD            (0X08) // RESET LCD
#define P5_4                 (0X10) // UNUSED
#define BUTTON2              (0X20) // PIN FOR BUTTON 2
#define BUTTON1              (0X40) // PIN FOR BUTTON 1
#define LCD_BACKLIGHT        (0X80) // PIN FOR LCD BACKLIGHT


// Port 6 Pins
#define UCA3TXD              (0X01) // SERIAL PORT TRANSMIT TO ?
#define UCA3RXD              (0X02) // SERIAL PORT RECEIVE FROM ?
#define J1_5                 (0X04) // UNUSED
#define MAG_INT              (0X08) // DONT CARE
#define P6_4                 (0X10) // UNUSED
#define P6_5                 (0X20) // UNUSED
#define P6_6                 (0X40) // UNUSED
#define P6_7                 (0X80) // UNUSED


//Port 7 Pins
#define I2CSDA               (0X01) // 
#define I2CSCL               (0X02) // 
#define SD_DETECT            (0X04) // 
#define J4_36                (0X08) // UNUSED
#define P7_4                 (0X10) // UNUSED
#define P7_5                 (0X20) // UNUSED
#define P7_6                 (0X40) // UNUSED
#define P7_7                 (0X80) // UNUSED


// Port 8 Pins
#define IR_LED               (0X01) // 
#define OPT_INT              (0X02) // 
#define TMP_INT              (0X04) // 
#define INT2                 (0X08) // 


// Port J Pins
#define PJ_0                 (0X01) // UNUSED
#define PJ_1                 (0X02) // UNUSED
#define PJ_2                 (0X04) // UNUSED
#define PJ_3                 (0X08) // UNUSED
#define LFXIN                (0X10) // LF CRYSTAL IN
#define LFXOUT               (0x20) // LF CRYSTAL OUT
#define HFXIN                (0x40) // HF CRYSTAL IN
#define HFXOUT               (0X80) // HF CRYSTAL OUT
#define CLEAR_REGISTER     (0X0000)


// For main.c


#define ALWAYS                  (1)
#define RESET_STATE             (0)
#define PORTS                (0x00) // PORTS
#define PWM_MODE             (0x01) // PWM_MODE



// For clocks.c

#define FLLN_BITS          (0x03ffu)
#define FLLN_255           (0x00ffu)
#define CSLOCK                (0x01) // Any incorrect password locks registers



// Other MACROS
#define RESET                 (0x00) // Null Value
#define HIGH                  (0xff) // High value
#define LOW                   (0x00) // Low value
#define LO                      &=~  // Macro for setting pins to zero
#define HI                       |=  // Macro for setting pins to one

#define TRUE                     (1) // True value
#define FALSE                    (0) // False value

#define L0                       (0) // First line of display
#define L1                       (1) // Second line of display
#define L2                       (2) // Third line of display
#define L3                       (3) // Fourth line of display
#define L4                       (4) // Number of rows
#define C0                       (0) // First column of display
#define C10                     (10) // 10th column of display
#define C11                     (11) // Number of columns

#define T25                     (25) // 25 for case statement
#define T50                     (50) // 50 for case statement
#define T75                     (75) // 75 for case statement
#define T100                   (100) // 100 for case statement
#define T125                   (125) // 125 for case statement


// Timer MACROS

#define TA0CCR0_INTERVAL      (50000) // Capture Control interval for blinking led's and general use (50000 = 0.1s)
#define TA1CCR0_INTERVAL      (50000) // Interval for Displaying ADC and time values (50000 = 0.1s)
#define LED_FLICK1               (10) // State 1 for LED flick
#define LED_FLICK2               (20) // State 2 for LED flick 
#define TA0CCR1_INTERVAL       (2500) // Capture Control interval for debounce timer
#define TA0CCR2_INTERVAL      (50000) // NOT USING!! (50000 = 0.1s)
#define TA1CCR1_INTERVAL        (7500) // Capture Control interval for checking car on line (7500 = 15ms)
#define TA1CCR2_INTERVAL       (50000) // Capture Control interval for getting wifi info and connecting/reconnecting to TCP (50000 = .1s)

#define OVERFLOW                 (140)          // OVERFLOW 
#define CCR1S                    (2)           // for switch statement
#define CCR2S                    (4)           // for switch statement
#define BOUNCETIME               (60)          // time to debounce for button press
#define DISPLAYTIME              (2)           // count for update_display

// Project 5


#define ONESEC                            (4)     // Number of intervals for one second
#define TWOSEC                            (8)     // Number of intervals for 2 seconds
#define THREESEC                          (12)    // Number of intervals for 3 seconds
#define HALFSEC                            (2)     // 


// Project 6


// MACROS for hex2dec.c ------------------------
#define NULL                            (0)
#define THOUSLESS                       (999)
#define THOUS                           (1000)
#define HUNDSLESS                        (99)
#define HUNDS                           (100)
#define TENSLESS                        (9)
#define TENS                            (10)
#define ASCIIZ                          (0x30)
#define THOUSPLACE                      (0)
#define HUNDSPLACE                      (1)
#define TENSPLACE                       (2)
#define ONESPLACE                       (3)
#define TENTHSPLACE                     (4)
#define PLUSONE                         (1)
#define TWOBYTES                        (5)
//----------------------------------------------


// States for state machine in Main

#define BUTTON1PRESSED                  (1)
#define BUTTON2PRESSED                  (2)
#define ADC_TIME_DISPLAY                (4)
#define T5                              (5)
#define AVGCNT                          (4)
#define REPLY                           (6)
#define CHECK                           '*'
#define RESET_IOT                       'R'
#define NEW_CHAR                        'N'
#define INTERCEPT                       'I'
#define TURNING                         'T'
#define WAITING                         'W'
#define FOLLOWING                       'F'
#define EXITING                         'E'


// PWM

#define LEFT_REVERSE_SPEED              TB0CCR3
#define LEFT_FORWARD_SPEED              TB0CCR4
#define RIGHT_REVERSE_SPEED             TB0CCR5
#define RIGHT_FORWARD_SPEED             TB0CCR6

#define WHEEL_OFF                       (0)
#define WHEEL_PERIOD                    (10000)

// Project 7
#define PRESSONCE                       (0)
#define PRESSTWICE                      (1)
#define PRESSTHIRD                      (2)
#define PRESSFOURTH                     (3)
#define PRESSFIFTH                      (4)

#define CIRCTIME                        (182)
#define WAITTIME                        (10)
#define TURNTIME                        (7)
#define DONETIME                        (20)

#define FORWARD                         (7000)
#define RIGHT_FORWARD                   (2400)
#define LEFT_FORWARD                    (2500)
#define DIVTWO                          (2)


// Homework 8
#define SMALL_RING_SIZE                 (16)
#define LARGE_RING_SIZE                 (32)
#define BEGINNING                       (0)
#define HIGH_BAUD                       'H'
#define LOW_BAUD                        'L'
#define LOWER_BAUD                      'D'
#define V6                              (0x06)
#define V18                             (18)
#define V8                              (0x08)
#define V0                              (0)
#define RXIFG                           (2)
#define TXIFG                           (4)
#define MESSAGE_OVER                    (12)
#define MESSAGE_SIZE                    (11)
#define CHAR0                           (0)                            
#define CHAR1                           (1)                            
#define CHAR2                           (2)                            
#define CHAR3                           (3)                            
#define CHAR4                           (4)                            
#define CHAR5                           (5)                            
#define CHAR6                           (6)                            
#define CHAR7                           (7)                            
#define CHAR8                           (8)                            
#define CHAR9                           (9)                            
#define CHAR10                          (10)                           
#define CHAR11                          (11)
#define CHAR12                          (12)
#define CHAR13                          (13)
#define CHAR14                          (14)
#define CHAR15                          (15)
#define CHAR16                          (16)
#define CNT_CORRECT                     (1)
#define BAUD_DEFAULT                    (52)               // 9600
#define DEFAULT_UCS_UCF_UCOS16          (0x4911)
#define BAUD_HIGH                       (1)                // 460800
#define HIGH_UCS_UCF_UCOS16             (0x4A11)
#define BAUD_LOW                        (4)                // 115200
#define LOW_UCS_UCF_UCOS16              (0x5551)


// Project 9

#define CARRIAGERETURN                  (0x0D)
#define LINEFEED                        (0x0A)
#define REGULAR                         (0)
#define COMMAND                         (1)
#define BIG_OL_SIZE                     (500)
#define FIRST                           (0)
#define SECOND                          (1)
#define THIRD                           (2)
#define FOURTH                          (3)
#define FIFTH                           (4)
#define RECORD                          (5)
#define SPACECHK                        (31)
#define SHIFT4                          (2)
#define SHIFT8                          (3)
#define SHIFT16                         (4)
#define SHIFT32                         (5)
#define SHIFT64                         (6)
#define SHIFT128                        (7)
#define SHIFT256                        (8)
#define SHIFT2048                       (11)
#define HALF_IP                         (9)
#define LARGE_SSID                      (28)
#define NODOT                           (0)
#define ONEDOT                          (1)
#define TWOPLUSDOT                      (2)
#define HALF                            /2
#define TIMESIZE                        (3)
#define COMMANDSIZE                     (3)
#define ZEROVAL                         (48)


// Project 10

#define MIN_SPEED                       (2000)
#define MAX_SPEED                       WHEEL_PERIOD - 200
#define SPEED_CHNG                      (200)
#define TURN_SPEED                      (9000)
#define SLOW_SPEED                      (2200)
#define S_TURN_SPEED                    (2800)
#define FAST                            (0)
#define SLOW                            (1)
#define LEFT                            (1)
#define RIGHT                           (2)
#define INT_SPEED_RIGHT                 (3450)
#define INT_SPEED_LEFT                  (6000)
#define FUDGE                           (500)
#define TURN_IR_ON                      (1)
#define IR_ON                           (2)
#define IR_TIME                         (25)
#define RESET_IOT_TIME                  (260)
#define EXIT_TIME                       (30)
#define CONNECT_TIME                    (16)
#define TCP_TIME                        (32)
#define TIME_IN_RESET                   (5)
