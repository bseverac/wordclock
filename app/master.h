#ifndef MASTER_HEADER
#define MASTER_HEADER

#include "../models/clock.h"
#include "../hardware/board.h"

class Master {

public:
  Master();
  void loop(int);
private:
  Clock clock;
  Board board;
};

#endif
