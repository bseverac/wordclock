#include <stdio.h>
#include <stdlib.h>

#include "matrice.h"

/////////////////////////////////////////////////////////////////
//TODO SPECIFIC CODE DO OTHER WAY ?
char displayed_char[CLOCK_H][CLOCK_W] ={
  {'W','I','L','B','E','S','T','U','D','E','U','X','I','O','J'},
  {'S','E','P','T','R','O','I','S','I','X','M','I','D','I','X'},
  {'M','I','N','U','I','T','C','I','N','Q','U','A','T','R','E'},
  {'U','N','E','N','E','U','F','O','N','Z','E','H','U','I','T'},
  {'H','E','U','R','E','S','E','G','E','T','M','O','I','N','S'},
  {'L','E','Q','U','A','R','A','N','T','E','V','I','N','G','T'},
  {'C','I','N','Q','U','A','N','T','E','T','R','E','N','T','E'},
  {'D','I','X','K','E','T','D','E','M','I','E','D','E','U','X'},
  {'Q','U','A','T','R','E','S','E','P','T','R','E','I','Z','E'},
  {'D','O','U','Z','E','H','U','I','T','R','O','I','S','I','X'},
  {'N','C','I','N','Q','U','A','R','T','I','S','E','I','Z','E'},
  {'U','N','E','Q','U','A','T','O','R','Z','E','N','E','U','F'},
  {'P','O','N','Z','E','B','A','M','I','N','U','T','E','S','T'}
};

void print_led(int x,int y, int led_status[CLOCK_H]){
  int status = led_status[y] & (1 << x);
  if(status){
    printf("%c", displayed_char[y][x]);
  }else{
    printf(".");
  }
}

void print_row(int y, int led_status[CLOCK_H]){
  for(int x=0 ; x < CLOCK_W ; x++){
    print_led(x, y, led_status);
  }
}

void print(int led_status[CLOCK_H]){
  for(int y=0 ; y < CLOCK_H ; y++){
    print_row(y, led_status);
    printf("\n");
  }
}
void print_binary(int n,int size, int max){
  int i =0;
  while (i++<size) {
    if (n & 1)
      printf("1");
    else
      printf("0");
    if(i!=0 && i%max == 0)
      printf("\n");
    n >>= 1;
  }
}
int get_bits(int val,int offset,int num_bits){
  return (val >> offset) & ((1<<num_bits)-1);
}
int offset_bits(int val, int offset){
  return val << offset;
}
int get_bits_MAX(int led_status[CLOCK_H], int first_row, int num_rows,int row_direction,int offset,int num_bits){
  int rows = first_row;
  int eat_row = 0;
  while(eat_row < num_rows){
    print_binary( get_bits(led_status[rows],offset,num_bits) ,num_bits, num_bits);
    rows+=row_direction;
    eat_row++;
  }
}
int get_bits_MAX1(int led_status[CLOCK_H]){
  return get_bits_MAX(led_status,CLOCK_H-1,6,-1,0,8);
}
int get_bits_MAX2(int led_status[CLOCK_H]){
  return get_bits_MAX(led_status,CLOCK_H-1,6,-1,8,7);
}
int get_bits_MAX3(int led_status[CLOCK_H]){
  return get_bits_MAX(led_status,0,7,1,8,7);
}
int get_bits_MAX4(int led_status[CLOCK_H]){
  return get_bits_MAX(led_status,0,7,1,0,8);
}
void print_debug_duino(int led_status[CLOCK_H]){
  for(int y=0 ; y < CLOCK_H ; y++){
    print_binary(led_status[y],CLOCK_W,15 );
  }
  printf("max1\n");
  get_bits_MAX1(led_status);
  printf("max2\n");
  get_bits_MAX2(led_status);
  printf("max3\n");
  get_bits_MAX3(led_status);
  printf("max4\n");
  get_bits_MAX4(led_status);

}
/////////////////////////////////////////////////////////////////


Matrice::Matrice(){
}

void Matrice::update(int led_status[CLOCK_H]){
  print(led_status);
  printf("\n");
  print_debug_duino(led_status);

}
