#ifndef MATRICE_HEADER
#define MATRICE_HEADER
#include "../app/config.h"

class Matrice {

public:
  Matrice();
  void set_intensity(int i);
  void update(LETTER_MATRIX);
};

#endif
