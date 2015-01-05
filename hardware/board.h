#ifndef BOARD_HEADER
#define BOARD_HEADER
#include "matrice.h"
#include "../app/config.h"
class Board {

public:
  Board();
  void update(LED_MATRIX);
private:
  Matrice matrice;
};

#endif
