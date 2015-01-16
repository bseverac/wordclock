#include "time.h"

Time::Time(){
  set(0,0,0,0);
}

Time::Time(int _hours, int _minutes, int _seconds, int _useconds){
  set(_hours,_minutes,_seconds,_useconds);
}

void Time::u_add(int amount){
  useconds+=amount;
  handle_time_boundary();
}
void Time::handle_time_boundary(){
  int num = 0;
  if(num = threshold_num(useconds,1000)){
    useconds = useconds % 1000;
    seconds += num;
    if(num = threshold_num(seconds,60)){
      seconds = seconds % 60;
      minutes += num;
      if(num = threshold_num(minutes,60)){
        minutes = minutes % 60;
        hours += num;
        if(num = threshold_num(hours,24)){
          hours = hours % 24;
        }
      }
    }
  }
}
int Time::threshold_num(int value, int threshold){
  return value / threshold;
}

bool Time::update_time_test(){
  hours++;
  if(hours>=24){
    hours-=24;
  }
  minutes++;
  if(minutes >=60){
    minutes =0;
  }
  return true;
}

void Time::set(int _hours, int _minutes, int _seconds, int _useconds){
  hours    = _hours;
  minutes  = _minutes;
  seconds  = _seconds;
  useconds = _useconds;
  handle_time_boundary();
}

int Time::get_hours()   { return hours;    }
int Time::get_minutes() { return minutes;  }
int Time::get_seconds() { return seconds;  }
int Time::get_useconds(){ return useconds; }
