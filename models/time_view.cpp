#include "time_view.h"
//configuration
//line 1
int IL_EST[2]=            {0,0b011011100000000};
int DEUX_H[2]=            {0,0b000000001111000};
int IL_EST_DEUX_H[2]=     {0,0b011011101111000};
//line 2
int SEPT_H[2]=            {1,0b111100000000000};
int TROIS_H[2]=           {1,0b000111110000000};
int SIX_H[2]=             {1,0b000000011100000};
int MIDI[2]=              {1,0b000000000011110};
int DIX_H[2]=             {1,0b000000000000111};
//line 3
int MINUIT[2]=            {2,0b111111000000000};
int CINQ_H[2]=            {2,0b000000111100000};
int QUATRE_H[2]=          {2,0b000000000111111};
//line 4
int UNE_H[2]=             {3,0b111000000000000};
int NEUF_H[2]=            {3,0b000111100000000};
int ONZE_H[2]=            {3,0b000000011110000};
int HUIT_H[2]=            {3,0b000000000001111};
//line 5
int HEURE[2]=             {4,0b111110000000000};
int HEURES[2]=            {4,0b111111000000000};
int MOINS[2]=             {4,0b000000000011111};
int H_ET[2]=              {4,0b000000001100000};
//line 6
int LE[2]=                {5,0b110000000000000};
int QUARANTE[2]=          {5,0b001111111100000};
int VINGT[2]=             {5,0b000000000011111};
//line 7
int CINQUANTE[2]=         {6,0b111111111000000};
int TRENTE[2]=            {6,0b000000000111111};
//line 8
int DIX[2]=               {7,0b111000000000000};
int D_ET[2]=              {7,0b000011000000000};
int DEMI[2]=              {7,0b000000111100000};
int DEUX[2]=              {7,0b000000000001111};
//line 9
int QUATRE[2]=            {8,0b111111000000000};
int SEPT[2]=              {8,0b000000111100000};
int TREIZE[2]=            {8,0b000000000111111};
//line 10
int DOUZE[2]=             {9,0b111110000000000};
int HUIT[2]=              {9,0b000001111000000};
int TROIS[2]=             {9,0b000000001111100};
int SIX[2]=               {9,0b000000000000111};
//line 11
int CINQ[2]=              {10,0b011110000000000};
int QUART[2]=             {10,0b000011111000000};
int SEIZE[2]=             {10,0b000000000011111};
//line 12
int UNE[2]=               {11,0b111000000000000};
int QUATORZE[2]=          {11,0b000111111110000};
int NEUF[2]=              {11,0b000000000001111};
//line 13
int ONZE[2]=              {12,0b011110000000000};
int MINUTES[2]=           {12,0b000000011111110};
int MINUTE[2]=            {12,0b000000011111100};

int * HOURS[12] = {MINUIT,UNE_H,DEUX_H,TROIS_H,QUATRE_H,CINQ_H,SIX_H,SEPT_H,HUIT_H,NEUF_H,DIX_H,ONZE_H};
int * C_MINUTES[9] = {UNE,DEUX,TROIS,QUATRE,CINQ,SIX,SEPT,HUIT,NEUF};
int * SEIZE_MINUTES[7] = {DIX,ONZE,DOUZE,TREIZE,QUATORZE,QUART,SEIZE};
int * DECIMAL[6]={0,DIX,VINGT,TRENTE,QUARANTE,CINQUANTE};

int START_MINUS = 40;

TimeView::TimeView(){
  enabled_demi = true;
}

void TimeView::perform(LetterMatrix * _letter_matrix, Time * _time){
  letter_matrix = _letter_matrix;
  letter_matrix->off();
  letter_matrix->light(IL_EST);
  int hours = _time->get_hours();
  int minutes = _time->get_minutes();
  if(minutes >= START_MINUS){
    hours = (hours + 1) % 24;
  }
  light_hours(hours);
  light_minutes(minutes);
}

void TimeView::light_hours(int hours){
  if(hours == 12){
    letter_matrix->light(MIDI);
  }else{
    letter_matrix->light(HOURS[hours%12]);
  }
  light_hour_word(hours);
}

void TimeView::light_minutes(int minutes){
  //gestion mot de liaison
  if(minutes==0) return;
  if(minutes >= START_MINUS){
    letter_matrix->light(MOINS);
    minutes = 60-minutes;
    if(minutes == 15) letter_matrix->light(LE);
  }else{
    letter_matrix->light(H_ET);
  }
  //gestion de "demi"
  if(minutes == 30 && enabled_demi){
    letter_matrix->light(DEMI);
    return;
  }
  //gestion minutes
  if(minutes > 10 && minutes <= 16){ // gestion des minutes de 10 à 16
    letter_matrix->light(SEIZE_MINUTES[minutes-10]);
  }else{
    light_minutes_number(minutes);
  }
  //
  light_minute_word(minutes);
}
void TimeView::light_hour_word(int hours){
  if(hours == 0 || hours == 12) return;
  if(hours%12 == 1){
    letter_matrix->light(HEURE);
  }else{
    letter_matrix->light(HEURES);
  }
}
void TimeView::light_minute_word(int minutes){
  if(minutes == 15) return;
  if(minutes !=1){
    letter_matrix->light(MINUTES);
  }else{
    letter_matrix->light(MINUTE);
  }
}
void TimeView::light_minutes_number(int minutes){
    int decimal = minutes/10;
    int unit = minutes%10;
    int * decimal_row = DECIMAL[decimal];
    if(decimal_row) letter_matrix->light(decimal_row);
    if(unit > 0){
      if(unit == 1 && decimal_row) letter_matrix->light(D_ET);
      letter_matrix->light(C_MINUTES[unit-1]);
    }
}
