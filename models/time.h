#ifndef TIME_HEADER
#define TIME_HEADER

class Time {

public:
  Time();
  Time(int,int,int,int);
  void u_add(int);
  void set(int,int,int,int);
  int get_hours();
  int get_minutes();
  int get_seconds();
  int get_useconds();
  bool update_time_test();
private:
  void handle_time_boundary();
  int threshold_num(int value, int threshold);
  int hours;
  int minutes;
  int seconds;
  int useconds;
};

#endif
