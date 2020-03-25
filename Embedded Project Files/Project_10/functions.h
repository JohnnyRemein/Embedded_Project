//******************************************************************************
//
//  Description: This file contains the Function prototypes
//
//  Jim Carlson
//  Aug 2013
//  Built with IAR Embedded Workbench Version: V4.10A/W32 (5.40.1)
//******************************************************************************
// Functions



// Project 9

void To_Display(char array[], int line);
void To_PC(char array[]);
void To_Wifi(char array[]);
void Parse_IP(void);

// Movement functions for Project 7
void Intercept(void);
void Waiting(void);
void Turning(void);
void DoneCircling(void);
void SlowStraight(void);

// Time counter for Project 7
char* MsecToSec(int msec_hunds);


// Move function for Project 5 and 9

void Command_Ex(char direction);
void Do_Moves(char array[]);
void No_Move(void);
void Forward(void);
void Reverse(void);
void Right(void);
void Left(void);
void Counter_Clock_Wise(void);
void Clock_Wise(void);

// Movement Functions for Project 4

void Run_Circle(void);
void Run_Triangle(void);
void Run_Figure(void);
void Run_Straight(void);
void wait_case(void);
void start_case(void);

// Initialization
void Init_Conditions(void);
void Clear_Display(void);

// Interrupts
void enable_interrupts(void);
__interrupt void TIMER0_A0_ISR(void);
__interrupt void Timer1_A0_ISR(void);
__interrupt void TIMER0_A1_ISR(void);
__interrupt void TIMER1_A1_ISR(void);
__interrupt void Timer0_B0_ISR(void);
__interrupt void TIMER0_B1_ISR(void);
__interrupt void switch_interrupt(void);
__interrupt void eUSCI_B0_ISR(void);
__interrupt void eUSCI_A0_ISR(void);
__interrupt void eUSCI_A3_ISR(void);

// Analog to Digital Converter
void Init_ADC(void);
void ADC_Process(void);
char* HEXtoBCD(int hex_value);
void adc_line3(void);
void adc_line4(char location);

// Clocks
void Init_Clocks(void);

// IOT
void IOT_Process(void);             // Process IOT messages
void check_iot_rec(void);
void determine_iot(void);
void iot_system_init(void);
void iot_meassage_type(void);
void iot_process(void);
void iot_process_simple(void);
void iot_clean_buffer(void);
void iot_test(void);
void IOT_SELECT_MODE(void);
void query_iot(void);
void iot_config(void);
void get_set_iot(char getset, char feature);
void iot_config_dump(void);
void set_network_iot(void);
void set_ssid_iot(char location);
void get_iot(void);
void set_iot(void);
void AT_iot(void);
void AT_factory(void);    // AT+F
void STS_iot(void);
void process_iot(void);
void iot_message(void);
void iot_message_ipaddr(char message_type);
void iot_message_ssid(unsigned int offset);
void iot_car_cntl(void);
void iot_write_data(void);
void set_iot_baudrate(char baud);
void iot_reset(void);
void change_comm(void);
void iot_factory_default(void);
void iot_hardware_reset(void);
void set_location_iot(char location);
void iot_class(void);
void iot_message_macaddr(void);
void send_ssid(void);
void iot_ping(void);
void iot_message_scanning(void);
void ip_addr(void);
void grab_char(void);

// LED Configurations
void Init_LEDs(void);
void IR_LED_control(char selection);
void Backlite_control(char selection);

  // LCD
void Display_Process(void);
void Display_Update(char p_L1,char p_L2,char p_L3,char p_L4);
void enable_display_update(void);
void update_string(char *string_data, int string);
void Init_LCD(void);
void lcd_clear(void);
void lcd_putc(char c);
void lcd_puts(char *s);

void lcd_power_on(void);
void lcd_write_line1(void);
void lcd_write_line2(void);
//void lcd_draw_time_page(void);
//void lcd_power_off(void);
void lcd_enter_sleep(void);
void lcd_exit_sleep(void);
//void lcd_write(unsigned char c);
//void out_lcd(unsigned char c);

void Write_LCD_Ins(char instruction);
void Write_LCD_Data(char data);
void ClrDisplay(void);
void ClrDisplay_Buffer_0(void);
void ClrDisplay_Buffer_1(void);
void ClrDisplay_Buffer_2(void);
void ClrDisplay_Buffer_3(void);

void SetPostion(char pos);
void DisplayOnOff(char data);
void lcd_BIG_mid(void);
void lcd_4line(void);
void lcd_out(char *s, char line, char position);
void lcd_rotate(char view);

//void lcd_write(char data, char command);
void lcd_write(unsigned char c);
void lcd_write_line1(void);
void lcd_write_line2(void);
void lcd_write_line3(void);


void lcd_command( char data);
void LCD_test(void);
void LCD_iot_meassage_print(int nema_index);
void display_ADC (void);

// Menu
void Menu_Process(void);


// Ports
void Init_Ports(void);
void Init_Port1(void);
void Init_Port2(void);
void Init_Port3(void);
void Init_Port4(void);
void Init_Port5(void);
void Init_Port6(void);
void Init_Port7(void);
void Init_Port8(void);
void Init_PortJ(void);

// Serial
void Init_Serial(void);
void Init_Serial_UCA0(void);
//void Init_Serial_UCA1(char speed);
void Init_Serial_UCA3(char baud_rate);
void Transmit_U(void);
void alphabet(void);
void outchar(char character);
void print_CR(void);
void menu(void);
void grab_a_character(void);
int wait_for_character(void);
void increment_usb_rx_ring(void);
void increment_iot_rx_ring(void);
void menu_program(void);
void outhex (unsigned int hexvalue);
void outshorthex (unsigned int hexvalue);
void out_wifi(char character);

// SPI
void Init_SPI_B1(void);
void SPI_B1_write(char byte);
void spi_rs_data(void);
void spi_rs_command(void);
void spi_LCD_idle(void);
void spi_LCD_active(void);
void SPI_test(void);
void WriteIns(char instruction);
void WriteData(char data);



//void LCD_PRINT(char *d, char line);
//void LCD_COMMAND( char cData);
//void LCD_INIT();
void delay_ms( int duration_time);

// Switches
void Init_Switches(void);
void switch_control(void);
void enable_switch_BUTTON1(void);
void enable_switch_BUTTON2(void);
void disable_switch_BUTTON1(void);
void disable_switch_BUTTON2(void);
void Switches_Process(void);
void Init_Switch(void);
void Switch_Process(void);
void Switch1_Process(void);
void Switch2_Process(void);
void menu_act(void);
void menu_select(void);

// Timers
void Init_Timers(void);
void Init_Timer_A0(void);
void Init_Timer_A1(void);
void Init_Timer_A2(void);
void Init_Timer_A3(void);
void Init_Timer_B0(void);
void Init_Timer_B1(void);
void Init_Timer_B2(void);

void usleep(unsigned int usec);
void usleep10(unsigned int usec);
void five_msec_sleep(unsigned int msec);
void measure_delay(void);
void out_control_words(void);

// Wheels
void WHEELS_test(void);
void Left_Motor_OFF(void);
void Right_Motor_OFF(void);
void Left_Motor_ON(char speed);
void Right_Motor_ON(char speed);
void Wheels(void);





