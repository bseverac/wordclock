#ifndef BOARD_HEADER
#define BOARD_HEADER
#include "matrice.h"
#include "../app/config.h"
class Board {

public:
  Board();
  void update(LETTER_MATRIX);
private:
  Matrice matrice;
};

#endif
