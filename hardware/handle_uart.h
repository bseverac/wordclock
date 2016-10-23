#ifndef HANDLE_UART
#define HANDLE_UART
#include "./lib-ino/twi.h"
#include "./lib-ino/rtc.h"
#include "./lib-ino/uart.h"
#include <stdio.h>

class HandleUart{
  char buf[32];
  int i;
  int start;
  int end;
  cBuffer * b;
  struct tm * t;

  public:

  int mode;
  int value;

  HandleUart();
  bool isCommand();
  void init();
  void handle();
  void handle_mode();
  void handle_ping();
  void handle_info();
  void handle_timeset();
  void handle_set();
  int get_two_digit(int i);
  char get(int i);
};
#endif
