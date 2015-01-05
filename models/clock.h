#ifndef CLOCK_HEADER
#define CLOCK_HEADER

#include "../app/config.h"

class Clock {

public:
  Clock();
  void loop(int);
  int led_status[CLOCK_H];

private:
  void print();
  void print_row(int y);
  void print_led(int x, int y);
  void off();
  void off(int x, int y);
  void set_led(int x, int y, bool status);
  void light(int * array);
  void update_led_status();
  void light_it_is();
  void light_hour();
  void light_minute();

  void update_time(int elapse);
  void handle_minutes(int*,int,int);
  void handle_hour_word();
  void handle_minute_word(int);
  //
  int iterator_x;
  int iterator_y;
  int hour;
  int minute;
  int second;
  int usecond;
  bool enabled_demi;

};

#endif
