#ifndef LETTER_MATRIX_HEADER
#define LETTER_MATRIX_HEADER

#include "../app/config.h"
#include "time.h"

class LetterMatrix {

public:
  LetterMatrix();
  void matrix_for_time(Time * time);
  int matrix[CLOCK_H];

  void off();
  void light(int * array);
private:
  void light_hours(int);
  void light_minutes(int);
  void light_minutes_number(int);
  void light_hour_word(int);
  void light_minute_word(int);
  //
  Time * time;
  int iterator_x;
  int iterator_y;
  int hour;
  int minute;
  int second;
  int usecond;
  bool enabled_demi;

};

#endif
