//------------------------------------------------------------------------------
//
//  Description: This file contains the initialization function required to set
//               up ADC
//
//  Jonathan Remein
//  9/23/18
//  Built with IAR Embedded Workbench Version: (7.12.1)
//------------------------------------------------------------------------------

#include "msp430.h"
#include "functions.h"
#include "macros.h"
#include <string.h>




void Init_ADC(void){
//------------------------------------------------------------------------------
// Configure ADC12
  
 ADC12CTL0 = RESET_STATE;
 
// ADC10CTL0 Register Description
// ADC12SHT1x ADC12_B sample-and-hold time. These bits define the number of ADC12CLK cycles in the
// sampling period for registers ADC12MEM8 to ADC12MEM23. Can be modified only when ADC12ENC=0.
 
// 0000 = 4 ADC12CLK cycles
// 0001 = 8 ADC12CLK cycles
// 0010 = 16 ADC12CLK cycles
// 0011 = 32 ADC12CLK cycles
// 0100 = 64 ADC12CLK cycles
// 0101 = 96 ADC12CLK cycles
// 0110 = 128 ADC12CLK cycles
// 0111 = 192 ADC12CLK cycles
// 1000 = 256 ADC12CLK cycles
// 1001 = 384 ADC12CLK cycles
// 1010 = 512 ADC12CLK cycles
 
 ADC12CTL0 |= ADC12SHT0_2; // 16 ADC clocks
 
// ADC12SHT0x ADC12_B sample-and-hold time. These bits define the number
// of ADC12CLK cycles in the sampling period for registers
// ADC12MEM0 to ADC12MEM7 and ADC12MEM24 to ADC12MEM31.
// Can be modified only when ADC12ENC = 0.
 
// 0000 = 4 ADC12CLK cycles
// 0001 = 8 ADC12CLK cycles
// 0010 = 16 ADC12CLK cycles
// 0011 = 32 ADC12CLK cycles
// 0100 = 64 ADC12CLK cycles
// 0101 = 96 ADC12CLK cycles
// 0110 = 128 ADC12CLK cycles
// 0111 = 192 ADC12CLK cycles
// 1000 = 256 ADC12CLK cycles
// 1001 = 384 ADC12CLK cycles
// 1010 = 512 ADC12CLK cycles
 
 ADC12CTL0 |= ADC12SHT1_2; // 16 ADC clocks
 
 // ADC12MSC ADC12_B multiple sample and conversion. Valid only for sequence
// or repeated modes. Can be modified only when ADC12ENC = 0.
// 0 = The sampling timer requires a rising edge of the SHI signal
// to triggereach sample-and-convert.
// 1 = The incidence of the first rising edge of the SHI signal
// triggers the sampling timer, but further sample-and-conversions
// are performed automatically as soon as the prior conversion
// is completed.
 
 ADC12CTL0 |= ADC12MSC; // The first rising edge of the SHI signal triggers the sampling timer
 
// ADC12ON ADC12_B on. Can be modified only when ADC12ENC = 0.
// 0 = ADC12_B off
// 1 = ADC12_B on
 
 ADC12CTL0 |= ADC12ON; // ADC12 on
 
// ADC12ENC ADC12_B enable conversion.
// 0 = ADC12_B disabled
// 1 = ADC12_B enabled
 
// Enable Conversion - to be done later
// ADC10CTL0 |= ADC10ENC; // Enable Conversion
 
// ADC12SC ADC12_B start conversion. Software-controlled sample-and-conversion
// start. ADC12SC and ADC12ENC may be set together with one instruction.
// ADC12SC is reset automatically.
// 0 = No sample-and-conversion-start
// 1 = Start sample-and-conversion
 
// Start Conversion - to be done later
// ADC10CTL0 |= ADC10SC; // Start Conversion
 
 
 
 
 
 
 
 // ADC12CTL1 Register Description
// ADC12CTL1 Can be modified only when ADC10CTL0 bit ADC10ENC = 0.
 ADC12CTL1 = RESET_STATE;
 
// ADC12PDIV ADC12_B pre divider. This bit pre divides the selected ADC12_B clock source.
// 00 = Pre divide by 1
// 01 = Pre divide by 4
// 10 = Pre divide by 32
// 11 = Pre divide by 64
 
 ADC12CTL1 |= ADC12PDIV_0; // Pre divide by 1
 
// ADC12SHSx ADC12_B sample-and-hold source select
// 000 = ADC12SC bit
// 001 = see the device-specific data sheet for source
// 010 = see the device-specific data sheet for source
// 011 = see the device-specific data sheet for source
// 100 = see the device-specific data sheet for source
// 101 = see the device-specific data sheet for source
// 110 = see the device-specific data sheet for source
// 111 = see the device-specific data sheet for source
 
 ADC12CTL1 |= ADC12SHS_0; // sample-and-hold source ADC12SC
 
// ADC12SHP ADC12_B sample-and-hold pulse-mode select. This bit selects
// the source of the sampling signal (SAMPCON) to be either the
// output of the sampling timer or the sample-input signal directly.
// 0 = SAMPCON signal is sourced from the sample-input signal.
// 1 = SAMPCON signal is sourced from the sampling timer.
 
 ADC12CTL1 |= ADC12SHP; // sourced from the sampling timer
// ADC12ISSH ADC12_B invert signal sample-and-hold.
// 0 = The sample-input signal is not inverted.
// 1 = The sample-input signal is inverted.
 
 ADC12CTL1 |= ADC12ISSH_0; // sample-input signal is not inverted
 
 // ADC12DIVx ADC12_B clock divider
// 000 = /1
// 001 = /2
// 010 = /3
// 011 = /4
// 100 = /5
// 101 = /6
// 110 = /7
// 111 = /8
 
 ADC12CTL1 |= ADC12DIV_0; // /1 clock divider
 
// ADC12SSELx ADC12_B clock source select
// 00 = ADC12OSC (MODOSC)
// 01 = ACLK
// 10 = MCLK
// 11 = SMCLK
 
 ADC12CTL1 |= ADC12SSEL0; // ADC12OSC (MODOSC)
 
// ADC12CONSEQx ADC12_B conversion sequence mode select. This bit should
// only be modified when ADC12ENC = 0 except to stop a conversion
// immediately by setting ADC12CONSEQx = 00 when ADC12ENC = 1.
// 00b = Single-channel, single-conversion
// 01b = Sequence-of-channels
// 10b = Repeat-single-channel
// 11b = Repeat-sequence-of-channels
 
 ADC12CTL1 |= ADC12CONSEQ_3; // Repeat-sequence-of-channels
 
// ADC12BUSY ADC12_B busy. This bit indicates an active sample or conversion
// operation.
// 0 = No operation is active.
// 1 = A sequence, sample, or conversion is active.
// This is a read value not a set value 
 
 
 
 
 
 
 
 // ADC12CTL2 Register Description
 
 ADC12CTL2 = RESET_STATE;
 
// ADC12RES ADC12_B resolution. This bit defines the conversion result resolution. This bit
// should only be modified when ADC12ENC=0.
// 00b = 8 bit (10 clock cycle conversion time)
// 01b = 10 bit (12 clock cycle conversion time)
// 10b = 12 bit (14 clock cycle conversion time)
// 11b = Reserved
 
 ADC12CTL2 |= ADC12RES_2; // 12-bit conversion results / 14 clock cycle conversion
 
// ADC12_B data read-back format. Data is always stored in the binary unsigned
// format.
// 0b = Binary unsigned. Theoretically for ADC12DIF = 0 and 12-bit mode the
// analog input voltage – VREF results in 0000h, the analog input
// voltage + VREF results in 0FFFh.
// 1b = Signed binary (2s complement), left aligned. Theoretically, for
// ADC12DIF = 0 and 12-bit mode, the analog input voltage – VREF
// results in 8000h, the analog input voltage + VREF results in 7FF0h.
 
 ADC12CTL2 |= ADC12DF_0; // Binary unsigned
 
// Enables ADC low-power mode for ADC12CLK with 1/4 the specified maximum
// for ADC12PWRMD = 0. This bit should only be modified when ADC12ENC = 0.
// 0b = Regular power mode where sample rate is not restricted
// 1b = Low power mode enable, ADC12CLK can not be greater than 1/4 the
// device-specific data sheet specified maximum for ADC12PWRMD = 0
 
 ADC12CTL2 |= ADC12PWRMD_0; // Regular power mode where sample rate is not restricted
 
 
 
 
 
 
 // ADC12CTL3 Register Description
 ADC12CTL3 = RESET_STATE;
 
// ADC12ICH3MAP Controls internal channel 3 selection to ADC input channel A26.
// Can be modified only when ADC12ENC = 0.
// 0b = external pin is selected for ADC input channel A26
// 1b = ADC input channel internal 3 is selected for ADC input channel A26, see
// device-specific data sheet for availability
 
 ADC12CTL3 |= ADC12ICH3MAP_0; // external pin is selected for ADC input channel A26
 
// ADC12ICH2MAP Controls internal channel 2 selection to ADC input channel A27.
// Can be modified only when ADC12ENC = 0.
// 0b = external pin is selected for ADC input channel A27
// 1b = ADC input channel internal 3 is selected for ADC input channel A27, see
// device-specific data sheet for availability
 
 ADC12CTL3 |= ADC12ICH2MAP_0; // external pin is selected for ADC input channel A27
 
// ADC12ICH1MAP Controls internal channel 1 selection to ADC input channel A28.
// Can be modified only when ADC12ENC = 0.
// 0b = external pin is selected for ADC input channel A28
// 1b = ADC input channel internal 3 is selected for ADC input channel A28, see
// device-specific data sheet for availability
 
 ADC12CTL3 |= ADC12ICH1MAP_0; // external pin is selected for ADC input channel A28
 
// ADC12ICH0MAP Controls internal channel 1 selection to ADC input channel A29.
// Can be modified only when ADC12ENC = 0.
// 0b = external pin is selected for ADC input channel A29
// 1b = ADC input channel internal 3 is selected for ADC input channel A29, see
// device-specific data sheet for availability
 
 ADC12CTL3 |= ADC12ICH0MAP_0; // external pin is selected for ADC input channel A29
 
// ADC12TCMAP Controls temperature sensor ADC input channel selection. Can be
// modified only when ADC12ENC = 0.
// 0b = external pin is selected for ADC input channel A30
// 1b = ADC internal temperature sensor channel is selected for ADC input channel A30
 
 ADC12CTL3 |= ADC12TCMAP_1; // ADC internal temperature sensor channel is
 // selected for ADC input channel A30
 
 // ADC12BATMAP Controls 1/2 AVCC ADC input channel selection. Can be modified
// only when ADC12ENC = 0.
// 0b = external pin is selected for ADC input channel A31
// 1b = ADC internal 1/2 x AVCC channel is selected for ADC input channel A31
 
 ADC12CTL3 |= ADC12BATMAP_1; // ADC internal 1/2 x AVCC channel is selected for
 // ADC input channel A31
 
// ADC12CSTARTADDx ADC12_B conversion start address. These bits select which
// ADC12_B conversion memory register is used for a single
// conversion or for the first conversion in a sequence. The
// value of CSTARTADDx is 0h to 1Fh, corresponding to ADC12MEM0
// to ADC12MEM31. Can be modified only when ADC12ENC = 0.
 
 ADC12CTL3 |= ADC12CSTARTADD_0; // ADC12MEM0 conversion start address
 
 
 
 
 
 
 
 // ADC12MCTL0 Register Description
 ADC12MCTL0 = RESET_STATE;
// ADC12WINC Comparator window enable. Can be modified only when ADC12ENC = 0.
// 0b = Comparator window disabled
// 1b = Comparator window enabled
// ADC12DIF Differential mode. Can be modified only when ADC12ENC = 0.
// 0b = Single-ended mode enabled
// 1b = Differential mode enabled
// ADC12VRSEL Selects combinations of VR+ and VR- sources as well as the buffer
// selection. Note: there is only one buffer so it can be used for
// either VR+ or VR-, but not both. Can be modified only when ADC12ENC = 0.
// 0000b = VR+ = AVCC, VR- = AVSS
// 0001b = VR+ = VREF buffered, VR- = AVSS
// 0010b = VR+ = VeREF-, VR- = AVSS
// 0011b = VR+ = VeREF+ buffered, VR- = AVSS
// 0100b = VR+ = VeREF+, VR- = AVSS
// 0101b = VR+ = AVCC, VR- = VeREF+ buffered
// 0110b = VR+ = AVCC, VR- = VeREF+
// 0111b = VR+ = VREF buffered, VR- = VeREF+
// 1000b = Reserved
// 1001b = VR+ = AVCC, VR- = VREF buffered
// 1010b = Reserved
// 1011b = VR+ = VeREF+, VR- = VREF buffered
// 1100b = VR+ = AVCC, VR- = VeREF-
// 1101b = VR+ = VREF buffered, VR- = VeREF-
// 1110b = VR+ = VeREF+, VR- = VeREF-
// 1111b = VR+ = VeREF+ buffered, VR- = VeREF-
// ADC12EOS End of sequence. Indicates the last conversion in a sequence.
// Can be modified only when ADC12ENC = 0.
// 0b = Not end of sequen
 
 // ADC12INCHx Input channel select. If even channels are set as differential,
// then odd channel configuration is ignored. Can be modified only
// when ADC12ENC = 0.
// 00000b = If ADC12DIF = 0: A0; If ADC12DIF = 1: Ain+ = A0, Ain- = A1
// 00001b = If ADC12DIF = 0: A1; If ADC12DIF = 1: Ain+ = A0, Ain- = A1
// 00010b = If ADC12DIF = 0: A2; If ADC12DIF = 1: Ain+ = A2, Ain- = A3
// 00011b = If ADC12DIF = 0: A3; If ADC12DIF = 1: Ain+ = A2, Ain- = A3
// 00100b = If ADC12DIF = 0: A4; If ADC12DIF = 1: Ain+ = A4, Ain- = A5
// 00101b = If ADC12DIF = 0: A5; If ADC12DIF = 1: Ain+ = A4, Ain- = A5
// 00110b = If ADC12DIF = 0: A6; If ADC12DIF = 1: Ain+ = A6, Ain- = A7
// 00111b = If ADC12DIF = 0: A7; If ADC12DIF = 1: Ain+ = A6, Ain- = A7
// 01000b = If ADC12DIF = 0: A8; If ADC12DIF = 1: Ain+ = A8, Ain- = A9
// 01001b = If ADC12DIF = 0: A9; If ADC12DIF = 1: Ain+ = A8, Ain- = A9
// 01010b = If ADC12DIF = 0: A10; If ADC12DIF = 1: Ain+ = A10, Ain- = A11
// 01011b = If ADC12DIF = 0: A11; If ADC12DIF = 1: Ain+ = A10, Ain- = A11
// 01100b = If ADC12DIF = 0: A12; If ADC12DIF = 1: Ain+ = A12, Ain- = A13
// 01101b = If ADC12DIF = 0: A13; If ADC12DIF = 1: Ain+ = A12, Ain- = A13
// 01110b = If ADC12DIF = 0: A14; If ADC12DIF = 1: Ain+ = A14, Ain- = A15
// 01111b = If ADC12DIF = 0: A15; If ADC12DIF = 1: Ain+ = A14, Ain- = A15
// 10000b = If ADC12DIF = 0: A16; If ADC12DIF = 1: Ain+ = A16, Ain- = A17
// 10001b = If ADC12DIF = 0: A17; If ADC12DIF = 1: Ain+ = A16, Ain- = A17
// 10010b = If ADC12DIF = 0: A18; If ADC12DIF = 1: Ain+ = A18, Ain- = A19
// 10011b = If ADC12DIF = 0: A19; If ADC12DIF = 1: Ain+ = A18, Ain- = A19
// 10100b = If ADC12DIF = 0: A20; If ADC12DIF = 1: Ain+ = A20, Ain- = A21
// 10101b = If ADC12DIF = 0: A21; If ADC12DIF = 1: Ain+ = A20, Ain- = A21
// 10110b = If ADC12DIF = 0: A22; If ADC12DIF = 1: Ain+ = A22, Ain- = A23
// 10111b = If ADC12DIF = 0: A23; If ADC12DIF = 1: Ain+ = A22, Ain- = A23
// 11000b = If ADC12DIF = 0: A24; If ADC12DIF = 1: Ain+ = A24, Ain- = A25
// 11001b = If ADC12DIF = 0: A25; If ADC12DIF = 1: Ain+ = A24, Ain- = A25
// 11010b = If ADC12DIF = 0: A26; If ADC12DIF = 1: Ain+ = A26, Ain- =A27
// 11011b = If ADC12DIF = 0: A27; If ADC12DIF = 1: Ain+ = A26, Ain- = A27
// 11100b = If ADC12DIF = 0: A28; If ADC12DIF = 1: Ain+ = A28, Ain- = A29
// 11101b = If ADC12DIF = 0: A29; If ADC12DIF = 1: Ain+ = A28, Ain- = A29
// 11110b = If ADC12DIF = 0: A30; If ADC12DIF = 1: Ain+ = A30, Ain- = A31
// 11111b = If ADC12DIF = 0: A31; If ADC12DIF = 1: Ain+ = A30, Ain- = A31
 
  ADC12MCTL0 = RESET_STATE;
 ADC12MCTL0 |= ADC12WINC_0; // Comparator window disabled
 ADC12MCTL0 |= ADC12DIF_0; // Single-ended mode enabled
 ADC12MCTL0 |= ADC12VRSEL_0; // VR+ = AVCC, VR- = AVSS
 ADC12MCTL0 |= ADC12INCH_2; // channel = A2
 ADC12MCTL1 = RESET_STATE;
 ADC12MCTL1 |= ADC12WINC_0; // Comparator window disabled
 ADC12MCTL1 |= ADC12DIF_0; // Single-ended mode enabled
 ADC12MCTL1 |= ADC12VRSEL_0; // VR+ = AVCC, VR- = AVSS
 ADC12MCTL1 |= ADC12INCH_4; // channel = A4 Right
 ADC12MCTL2 = RESET_STATE;
 ADC12MCTL2 |= ADC12WINC_0; // Comparator window disabled
 ADC12MCTL2 |= ADC12DIF_0; // Single-ended mode enabled
 ADC12MCTL2 |= ADC12VRSEL_0; // VR+ = AVCC, VR- = AVSS
 ADC12MCTL2 |= ADC12INCH_5; // channel = A5 Left
 ADC12MCTL2 |= ADC12EOS; // End of Sequence
 ADC12IER0 |= ADC12IE2; //Generate Interrupt for MEM2 ADC Data load
// ADC12IER0 |= ADC12IE0; // Enable ADC conv complete interrupt
 ADC12CTL0 |= ADC12ENC; // Enable conversion
 ADC12CTL0 |= ADC12SC; // Start sampling
//------------------------------------------------------------------------------
}




/*
void Init_ADC(void){
//------------------------------------------------------------------------------
// Configure ADC12

// ADC10CTL0 Register Description
  ADC12CTL0 = RESET_STATE;
  ADC12CTL0 |= ADC12SHT0_2;     // 16 ADC clocks
  ADC12CTL0 |= ADC12SHT1_2;     // 16 ADC clocks
  ADC12CTL0 |= ADC12MSC;        // First rising edge SHI signal triggers sampling timer
  ADC12CTL0 |= ADC12ON;         // ADC12 on

// ADC10CTL1 Register Description
  ADC12CTL1 = RESET_STATE;
  ADC12CTL1 |= ADC12PDIV_0;     // Predivide ADC12_B clock source by 1
  ADC12CTL1 |= ADC12SHS_0;      // sample-and-hold source ADC12SC
  ADC12CTL1 |= ADC12SHP;      // SAMPCON signal is sourced from the sampling timer.
  ADC12CTL1 |= ADC12ISSH_0;     // sample-input signal is not inverted
  ADC12CTL1 |= ADC12DIV_0;      // / 1 clock divider
  ADC12CTL1 |= ADC12SSEL0;      // ADC12OSC (MODOSC)
  ADC12CTL1 |= ADC12CONSEQ_3;   // Repeat-sequence-of-channels

// ADC12CTL2 Register Description
  ADC12CTL2 = RESET_STATE;
  ADC12CTL2 |= ADC12RES_2;      // 12-bit conversion results / 14 clock cycle conversion
  ADC12CTL2 |= ADC12DF_0;       // Binary unsigned
  ADC12CTL2 |= ADC12PWRMD_0;    // Regular power mode where sample rate is not restricted

// ADC12CTL3 Register Description
  ADC12CTL3 = RESET_STATE;
  ADC12CTL3 |= ADC12ICH3MAP_0;  // external pin is selected for ADC input channel A26
  ADC12CTL3 |= ADC12ICH2MAP_0;  // external pin is selected for ADC input channel A27
  ADC12CTL3 |= ADC12ICH1MAP_0;  // external pin is selected for ADC input channel A28
  ADC12CTL3 |= ADC12ICH0MAP_0;  // external pin is selected for ADC input channel A29
  ADC12CTL3 |= ADC12TCMAP_1;    // ADC internal temperature sensor ADC input channel A30
  ADC12CTL3 |= ADC12BATMAP_1;   // ADC internal 1/2 x AVCC is ADC input channel A31
  ADC12CTL3 |= ADC12CSTARTADD_0; // 0h to 1Fh, corresponding to ADC12MEM0 to ADC12MEM31

// ADC10MCTL0 Register Description
  ADC12MCTL0 = RESET_STATE;
  ADC12MCTL0 |= ADC12WINC_0;    // Comparator window disabled
  ADC12MCTL0 |= ADC12DIF_0;     // Single-ended mode enabled
  ADC12MCTL0 |= ADC12VRSEL_0;   // VR+ = AVCC, VR- = AVSS
  ADC12MCTL0 |= ADC12INCH_2;    // channel = A2 Thumb Wheel

  ADC12MCTL1 = RESET_STATE;
  ADC12MCTL1 |= ADC12WINC_0;  // Comparator window disabled
  ADC12MCTL1 |= ADC12DIF_0;   // Single-ended mode enabled
  ADC12MCTL1 |= ADC12VRSEL_0; // VR+ = AVCC, VR- = AVSS
  ADC12MCTL1 |= ADC12INCH_5;  // channel = A5 Left

  ADC12MCTL2 = RESET_STATE;
  ADC12MCTL2 |= ADC12WINC_0;  // Comparator window disabled
  ADC12MCTL2 |= ADC12DIF_0;   // Single-ended mode enabled
  ADC12MCTL2 |= ADC12VRSEL_0; // VR+ = AVCC, VR- = AVSS
  ADC12MCTL2 |= ADC12INCH_4;  // channel = A4 Right

  ADC12MCTL3 = RESET_STATE;
  ADC12MCTL3 |= ADC12WINC_0;  // Comparator window disabled
  ADC12MCTL3 |= ADC12DIF_0;   // Single-ended mode enabled
  ADC12MCTL3 |= ADC12VRSEL_0; // VR+ = AVCC, VR- = AVSS
  ADC12MCTL3 |= ADC12INCH_30; // Temp sensor

  ADC12MCTL4 = RESET_STATE;
  ADC12MCTL4 |= ADC12WINC_0;  // Comparator window disabled
  ADC12MCTL4 |= ADC12DIF_0;   // Single-ended mode enabled
  ADC12MCTL4 |= ADC12VRSEL_0; // VR+ = AVCC, VR- = AVSS
  ADC12MCTL4 |= ADC12INCH_31; // Battery voltage monitor
  ADC12MCTL4 |= ADC12EOS;     // End of Sequence

// ADC12IER0-2 Register Descriptions
  ADC12IER0 = RESET_STATE;    // Interrupts for channels  0 - 15
  ADC12IER1 = RESET_STATE;    // Interrupts for channels 16 - 31
  ADC12IER2 = RESET_STATE;    // Interrupts for ADC12RDYIE ADC12TOVIE ADC12OVIE
                              // ADC12HIIE ADC12LOIE ADC12INIE
							  
  ADC12IER0 |= ADC12IE4;      // Generate Interrupt for MEM2 ADC Data load//
//  ADC12IER0 |= ADC12IE2;    // Generate Interrupt for MEM2 ADC Data load
//  ADC12IER0 |= ADC12IE0;    // Enable ADC conv complete interrupt

  ADC12CTL0 |= ADC12ENC;     // Start conversion
  ADC12CTL0 |= ADC12SC;      // Start sampling
//------------------------------------------------------------------------------
}
*/
