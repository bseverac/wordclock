#include "clock.h"

//1
int IL_EST[2]=            {0,0b011011100000000};
int DEUX_H[2]=            {0,0b000000001111000};
int IL_EST_DEUX_H[2]=     {0,0b011011101111000};
//2
int SEPT_H[2]=            {1,0b111100000000000};
int TROIS_H[2]=           {1,0b000111110000000};
int SIX_H[2]=             {1,0b000000011100000};
int MIDI[2]=              {1,0b000000000011110};
int DIX_H[2]=             {1,0b000000000000111};
//3
int MINUIT[2]=            {2,0b111111000000000};
int CINQ_H[2]=            {2,0b000000111100000};
int QUATRE_H[2]=          {2,0b000000000111111};
//4
int UNE_H[2]=             {3,0b111000000000000};
int NEUF_H[2]=            {3,0b000111100000000};
int ONZE_H[2]=            {3,0b000000011110000};
int HUIT_H[2]=            {3,0b000000000001111};
//5
int HEURE[2]=             {4,0b111110000000000};
int HEURES[2]=            {4,0b111111000000000};
int MOINS[2]=             {4,0b000000000011111};
int H_ET[2]=              {4,0b000000001100000};
//6
int LE[2]=                {5,0b110000000000000};
int QUARANTE[2]=          {5,0b001111111100000};
int VINGT[2]=             {5,0b000000000011111};
//7
int CINQUANTE[2]=         {6,0b111111111000000};
int TRENTE[2]=            {6,0b000000000111111};
//8
int DIX[2]=               {7,0b111000000000000};
int ET[2]=                {7,0b000011000000000};
int DEMI[2]=              {7,0b000000111100000};
int DEUX[2]=              {7,0b000000000001111};
//9
int QUATRE[2]=            {8,0b111111000000000};
int SEPT[2]=              {8,0b000000111100000};
int TREIZE[2]=            {8,0b000000000111111};
//10
int DOUZE[2]=             {9,0b111110000000000};
int HUIT[2]=              {9,0b000001111000000};
int TROIS[2]=             {9,0b000000001111100};
int SIX[2]=               {9,0b000000000000111};
//11
int CINQ[2]=              {10,0b011110000000000};
int QUART[2]=             {10,0b000011111000000};
int SEIZE[2]=             {10,0b000000000011111};
//12
int UNE[2]=               {11,0b111000000000000};
int QUATORZE[2]=          {11,0b000111111110000};
int NEUF[2]=              {11,0b000000000001111};
//13
int ONZE[2]=              {12,0b011110000000000};
int MINUTES[2]=           {12,0b000000011111110};
int MINUTE[2]=            {12,0b000000011111100};

int * HOURS[12] = {MINUIT,UNE_H,DEUX_H,TROIS_H,QUATRE_H,CINQ_H,SIX_H,SEPT_H,HUIT_H,NEUF_H,DIX_H,ONZE_H};
int * C_MINUTES[9] = {UNE,DEUX,TROIS,QUATRE,CINQ,SIX,SEPT,HUIT,NEUF};
int * SEIZE_MINUTES[7] = {DIX,ONZE,DOUZE,TREIZE,QUATORZE,QUART,SEIZE};
int * DECIMAL[6]={0,DIX,VINGT,TRENTE,QUARANTE,CINQUANTE};

Clock::Clock(){
  hour = 5;
  minute = 35;
  second = 0;
  usecond = 0;
  enabled_demi = true;
  off();
}

void Clock::loop(int elapse){
  //update_time(elapse);
  update_led_status();
}

void Clock::off(){
  for(iterator_y=0 ; iterator_y < CLOCK_H ; iterator_y++){
    led_status[iterator_y] = 0;
  }
}

void Clock::light(int * array){
  iterator_y = array[0];
  led_status[iterator_y]= led_status[iterator_y] | array[1];
}

void Clock::update_time(int elapse){
  hour++;
  if(hour>=24){
    hour-=24;
  }
  minute++;
  if(minute >=60){
    minute =0;
  }
  //
  usecond+=elapse;
  if(usecond>=1000){
    usecond-=1000;
    second++;
    if(second >= 60){
      second -= 60;
      minute++;
      if(minute >=60){
        minute -=60;
        hour++;
        if(hour>=24){
          hour-=24;
        }
      }
    }
  }
}


void Clock::update_led_status(){
  off();
  light_it_is();
  light_hour();
  light_minute();
}

void Clock::light_it_is(){
  light(IL_EST);
}

void Clock::light_hour(){
  if(hour == 12){
    light(MIDI);
  }else{
    light(HOURS[hour%12] );
  }
  handle_hour_word();
}

void Clock::light_minute(){
  int value = minute;
  //gestion mot de liaison
  if(value==0) return;
  if(value >= 40){
    light(MOINS);
    value = 60-value;
    if(value == 15) light(LE);
  }else{
    light(H_ET);
  }
  //gestion de "demi"
  if(value == 30 && enabled_demi){
    light(DEMI);
    return;
  }
  //gestion minutes
  if(value > 10 && value <= 16){ // gestion des minutes de 10 à 16
    light(SEIZE_MINUTES[value-10]);
  }else{
    int decimal = value/10;
    handle_minutes(DECIMAL[decimal],decimal*10,value);
  }
  //
  handle_minute_word(value);
}
void Clock::handle_hour_word(){
  if(hour == 0 || hour == 12) return;
  if(hour%12 == 1){
    light(HEURE);
  }else{
    light(HEURES);
  }
}
void Clock::handle_minute_word(int value){
  if(value == 15) return;
  if(value !=1){
    light(MINUTES);
  }else{
    light(MINUTE);
  }
}
void Clock::handle_minutes(int * array,int ref, int value){
    if(array) light(array);
    if(value > ref){
      if(value-ref == 1 && array) light(ET);
      light(C_MINUTES[value-ref-1]);
    }
}
