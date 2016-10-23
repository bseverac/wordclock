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

#define	MAX72XX_DIN_PIN		2
#define	MAX72XX_DIN_DDR		DDRD
#define	MAX72XX_DIN_PORT	PORTD

#define	MAX72XX_LOAD_PIN	3
#define	MAX72XX_LOAD_DDR	DDRD
#define	MAX72XX_LOAD_PORT	PORTD

#define	MAX72XX_CLK_PIN		4
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

void invert_write_byte(int data){
  int i = 0;
  while(i < 7){
    set0(MAX72XX_CLK_PORT, MAX72XX_CLK_PIN);		// clock down - this clocks out the bit to DOUT
    if(data & (0b00000001 << i))					// take the bit to send
    {
      set1(MAX72XX_DIN_PORT, MAX72XX_DIN_PIN);	// logical 1
    }else{
      set0(MAX72XX_DIN_PORT, MAX72XX_DIN_PIN);	// logical 0
    }
    set1(MAX72XX_CLK_PORT, MAX72XX_CLK_PIN);		// clock up - take the bit - @8MHz this lasts 125ns, which is > 50ns that is required by the MAX chip, so OK!
    i++;
  }
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

void setup(int i) {
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
  maxAll(max7219_reg_intensity, 0xff & i);    // the first 0x0f is the value you can set
  for(int col=0;col<8;col++){
    maxAll(col+1,0x00);
  }
}

int get_bits(int val,int offset,int num_bits){
  return (val >> offset) & ((1<<num_bits)-1);
}
int offset_bits(int val, int offset){
  return val << offset;
}
void print_none(){
  write_byte(0);
}

int print_row_MAX(int led_status[CLOCK_H], int row, int offset, int num_bits, int id){
  write_byte(get_bits(led_status[row],offset,num_bits)<<(8-num_bits));
}
void print_row_MAX1(int row, int led_status[CLOCK_H]){
  if(row<6){
    print_row_MAX(led_status,CLOCK_H-1-1*row,7,8,1);
  }else if(row == 7){
    write_byte(0x0);
  }else{
    print_none();
  }
}
void print_row_MAX2(int row, int led_status[CLOCK_H]){
  if(row<6){
    print_row_MAX(led_status,CLOCK_H-1-1*row,0,7,2);
  }else if(row == 7){
    write_byte(0x0);
  }else{
    print_none();
  }
}
void print_row_MAX3(int row, int led_status[CLOCK_H]){
  if(row<7){
    print_row_MAX(led_status,1*row,0,7,3);
  }else if(row == 7){
    write_byte(0x0);
  }else{
    print_none();
  }
}
void print_row_MAX4(int row, int led_status[CLOCK_H]){
  if(row<7){
    print_row_MAX(led_status,1*row,7,8,4);
  }else if(row == 7){
    write_byte(0x0);
  }else{
    print_none();
  }
}

Matrice::Matrice(){
  setup(0xFF);
}

void Matrice::set_intensity(int i){
  setup(i);
}

void Matrice::update(int led_status[CLOCK_H]){
  for(int col=0;col<8;col++){
    set0(MAX72XX_LOAD_PORT, MAX72XX_LOAD_PIN);
    write_byte(col+1);
    //write_byte(255);
    print_row_MAX4(col, led_status);
    write_byte(col+1);
    //write_byte(255);
    print_row_MAX3(col, led_status);
    write_byte(col+1);
    //write_byte(255);
    print_row_MAX2(col, led_status);
    write_byte(col+1);
    //write_byte(255);
    print_row_MAX1(col, led_status);
    set1(MAX72XX_LOAD_PORT, MAX72XX_LOAD_PIN);		// MAX "loads" data on rising edge of LOAD line - this also has to last > 50ns, and @8MHz it does so it is OK
    set0(MAX72XX_LOAD_PORT, MAX72XX_LOAD_PIN);		// get back to zero
  }
}
