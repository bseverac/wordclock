#ifndef TIME_HEADER
#define TIME_HEADER

class Time {

public:
  Time();
  void u_add(int);
  void set(int);
  int get_hour();
  int get_minute();
  int get_second();
  int get_usecond();

private:
  int hour;
  int minute;
  int second;
  int usecond;
};

#endif
