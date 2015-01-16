#include "board.h"
#include "../app/config.h"

Board::Board(){
}

void Board::update(int letter_status[CLOCK_H]){
  matrice.update(letter_status);
}
