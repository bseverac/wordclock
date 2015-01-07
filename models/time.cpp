#include "time.h"

Time::Time(){
  hour    = 0;
  minute  = 0;
  second  = 0;
  usecond = 0;
}

void Time::u_add(int amount){
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

void Time::increment_test(){
  hour++;
  if(hour>=24){
    hour-=24;
  }
  minute++;
  if(minute >=60){
    minute =0;
  }
}
