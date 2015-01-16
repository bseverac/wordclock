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
  int status = led_status[y] & (1 << (14-x));
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

/////////////////////////////////////////////////////////////////

Matrice::Matrice(){
}

void Matrice::update(int led_status[CLOCK_H]){
  print(led_status);
  printf("\n");
}
