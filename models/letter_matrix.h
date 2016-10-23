#ifndef LETTER_MATRIX_HEADER
#define LETTER_MATRIX_HEADER

#include "../app/config.h"

class LetterMatrix {

public:
  LetterMatrix();
  int matrix[CLOCK_H];

  void off();
  void light(int * array);
  void light(int, int);
  void off(int, int);
  bool status(int, int);
private:
  int iterator_x;
  int iterator_y;
};

#endif
