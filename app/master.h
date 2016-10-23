#ifndef MASTER_HEADER
#define MASTER_HEADER

#include "../models/letter_matrix.h"
#include "../models/time.h"
#include "../models/time_view.h"
#include "../hardware/board.h"

class Master {

public:
  Master();
  void loop(int, int);
  void update_time(int);
  void set_time(int, int, int);
private:
  int value;
  int test(int);
  int iterator;
  TimeView time_view;
  Time time;
  LetterMatrix letter_matrix;
  Board board;
};

#endif
