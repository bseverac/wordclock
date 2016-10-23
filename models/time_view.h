#ifndef TIME_VIEW_HEADER
#define TIME_VIEW_HEADER

#include "../app/config.h"
#include "time.h"
#include "letter_matrix.h"

class TimeView {

public:
  TimeView();
  LetterMatrix * letter_matrix;
  void perform(LetterMatrix * letter_matrix, Time * time);
private:
  void light_hours(int);
  void light_minutes(int);
  void light_minutes_number(int);
  void light_hour_word(int);
  void light_minute_word(int);
  bool enabled_demi;
};

#endif
