#include "board.h"
#include "../app/config.h"

Board::Board(){
}

void Board::update(int led_status[CLOCK_H]){
  matrice.update(led_status);
}
