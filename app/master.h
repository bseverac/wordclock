#ifndef MASTER_HEADER
#define MASTER_HEADER

#include "../models/letter_matrix.h"
#include "../models/time.h"
#include "../hardware/board.h"

class Master {

public:
  Master();
  void loop(int);
private:
  Time time;
  LetterMatrix letter_matrix;
  Board board;
};

#endif
