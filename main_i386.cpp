//essai du code c sous gcc et windows
#include <stdio.h>
#include <stdlib.h>

#include "app/master.h"
#include <time.h>

#include <iostream>

#ifdef WIN32
#include <windows.h>
#else
#include <unistd.h>
#endif // win32

void sleepcp(int milliseconds);

void sleepcp(int milliseconds) // cross-platform sleep function
{
  #ifdef WIN32
  Sleep(milliseconds);
  #else
  usleep(milliseconds * 1000);
  #endif // win32
}

int main()
{
  Master master;
  while(1){
    master.loop(1000);
    sleepcp(10000);
  }
}
