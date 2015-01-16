#include "master.h"

Master::Master(){
}

void Master::loop(int elapse){
  //time.u_add(elapse);
  time.update_time_test();
  letter_matrix.matrix_for_time(&time);
  board.update(letter_matrix.matrix);
}
