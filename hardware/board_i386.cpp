#include "board.h"
#include "../app/config.h"
#ifdef WIN32
#include <windows.h>
#else
#include <unistd.h>
#include <stdlib.h>
#endif // win32

Board::Board(){
}

void Board::update(int led_status[CLOCK_H]){
  #ifdef WIN32
  system("CLS");
  #else
  system("clear");
  #endif
  matrice.update(led_status);
}
