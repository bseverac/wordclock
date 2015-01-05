#include "matrice.h"
#include <stdio.h>
#include <avr/io.h>
#include <avr/interrupt.h>
#include <avr/pgmspace.h>
#include <stdlib.h> // just for random nrs
#include <avr/eeprom.h>
#include <string.h>
////////////////////////////////////////////////////////////////////CONFIG
#define set0(port, pin)			( (port) &= (int)~_BV(pin) )
#define set1(port, pin)			( (port) |= (int)_BV(pin) )

#define	MAX72XX_DIN_PIN		0
#define	MAX72XX_DIN_DDR		DDRB
#define	MAX72XX_DIN_PORT	PORTB

#define	MAX72XX_LOAD_PIN	6
#define	MAX72XX_LOAD_DDR	DDRD
#define	MAX72XX_LOAD_PORT	PORTD

#define	MAX72XX_CLK_PIN		7
#define	MAX72XX_CLK_DDR		DDRD
#define	MAX72XX_CLK_PORT	PORTD

int maxInUse = 4;    //change this variable to set how many MAX7219's you'll use
////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////
int e = 0;           // just a varialble

// define max7219 registers
int max7219_reg_noop        = 0x00;
int max7219_reg_digit0      = 0x01;
int max7219_reg_digit1      = 0x02;
int max7219_reg_digit2      = 0x03;
int max7219_reg_digit3      = 0x04;
int max7219_reg_digit4      = 0x05;
int max7219_reg_digit5      = 0x06;
int max7219_reg_digit6      = 0x07;
int max7219_reg_digit7      = 0x08;
int max7219_reg_decodeMode  = 0x09;
int max7219_reg_intensity   = 0x0a;
int max7219_reg_scanLimit   = 0x0b;
int max7219_reg_shutdown    = 0x0c;
int max7219_reg_displayTest = 0x0f;

void write_byte(int data){
  int i = 8;
  while(i-- > 0)
  {
  set0(MAX72XX_CLK_PORT, MAX72XX_CLK_PIN);		// clock down - this clocks out the bit to DOUT
  if(data & (0b00000001 << i))					// take the bit to send
    {
      set1(MAX72XX_DIN_PORT, MAX72XX_DIN_PIN);	// logical 1
    }
    else
      {
        set0(MAX72XX_DIN_PORT, MAX72XX_DIN_PIN);	// logical 0
      }
      set1(MAX72XX_CLK_PORT, MAX72XX_CLK_PIN);		// clock up - take the bit - @8MHz this lasts 125ns, which is > 50ns that is required by the MAX chip, so OK!
    }
    // we leave with CLK line left HIGH, which is no problem...
    return;
}

void maxAll (int reg, int col) {    // initialize  all  MAX7219's in the system
  int c = 0;
  set0(MAX72XX_LOAD_PORT, MAX72XX_LOAD_PIN);
  for ( c =1; c<= maxInUse; c++) {
    write_byte(reg);  // specify register
    write_byte(col);//((data & 0x01) * 256) + data >> 1); // put data
  }
  set1(MAX72XX_LOAD_PORT, MAX72XX_LOAD_PIN);		// MAX "loads" data on rising edge of LOAD line - this also has to last > 50ns, and @8MHz it does so it is OK
  set0(MAX72XX_LOAD_PORT, MAX72XX_LOAD_PIN);		// get back to zero
}

////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////

void setup() {
  MAX72XX_DIN_DDR |= _BV(MAX72XX_DIN_PIN);
  MAX72XX_LOAD_DDR |= _BV(MAX72XX_LOAD_PIN);
  MAX72XX_CLK_DDR |= _BV(MAX72XX_CLK_PIN);

  // pin-states
  set1(MAX72XX_LOAD_PORT, MAX72XX_LOAD_PIN);
  set0(MAX72XX_DIN_PORT, MAX72XX_DIN_PIN);
  set0(MAX72XX_CLK_PORT, MAX72XX_CLK_PIN);
  //initiation of the max 7219
  maxAll(max7219_reg_scanLimit, 0x07);
  maxAll(max7219_reg_decodeMode, 0x00);  // using an led matrix (not digits)
  maxAll(max7219_reg_shutdown, 0x01);    // not in shutdown mode
  maxAll(max7219_reg_displayTest, 0x00); // no display test
  maxAll(max7219_reg_intensity, 0x00 & 0x0f);    // the first 0x0f is the value you can set
}

int get_bits(int val,int offset,int num_bits){
  return (val >> offset) & ((1<<num_bits)-1);
}
int offset_bits(int val, int offset){
  return val << offset;
}
int print_bits_MAX(int led_status[CLOCK_H], int first_row, int num_rows,int row_direction,int offset,int num_bits, int id){
  int rows = first_row;
  int eat_row = 0;
  while(eat_row < num_rows){
    write_byte(get_bits(led_status[rows],offset,num_bits));
    rows+=row_direction;
    eat_row++;
  }
}
int print_bits_MAX1(int led_status[CLOCK_H]){
  return print_bits_MAX(led_status,CLOCK_H-1,6,-1,0,8,1);
}
int print_bits_MAX2(int led_status[CLOCK_H]){
  return print_bits_MAX(led_status,CLOCK_H-1,6,-1,8,7,2);
}
int print_bits_MAX3(int led_status[CLOCK_H]){
  return print_bits_MAX(led_status,0,7,1,8,7,3);
}
int print_bits_MAX4(int led_status[CLOCK_H]){
  return print_bits_MAX(led_status,0,7,1,0,8,4);
}

Matrice::Matrice(){
  setup();
}

void Matrice::update(int led_status[CLOCK_H]){
  set0(MAX72XX_LOAD_PORT, MAX72XX_LOAD_PIN);
  print_bits_MAX1(led_status);
  print_bits_MAX2(led_status);
  print_bits_MAX3(led_status);
  print_bits_MAX4(led_status);
  set1(MAX72XX_LOAD_PORT, MAX72XX_LOAD_PIN);		// MAX "loads" data on rising edge of LOAD line - this also has to last > 50ns, and @8MHz it does so it is OK
  set0(MAX72XX_LOAD_PORT, MAX72XX_LOAD_PIN);		// get back to zero
}
