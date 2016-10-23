#include "master.h"

Master::Master(){
  iterator = 100;
  value = 0xFF;
}

void Master::set_time(int h, int m, int s){
  if(s == 0){
    board.set_intensity(value/2);
  }
  if(s == 1){
    board.set_intensity(value);
  }
  time.set(h, m, s, 0);
}

void Master::update_time(int elapse){
  time.u_add(elapse);
}
void Master::loop(int mode, int _value){
  if(value != _value){
    value = _value;
    board.set_intensity(value);
  }
  if(mode == 0){
    time_view.perform(&letter_matrix, &time);
    board.update(letter_matrix.matrix);
  }else{
    letter_matrix.off();
    for(int iterator_y=0 ; iterator_y < CLOCK_H ; iterator_y++){
      letter_matrix.light(test(iterator + iterator_y), iterator_y);
      letter_matrix.light(test(iterator + iterator_y + 1), iterator_y);
      letter_matrix.light(test(iterator + iterator_y + 2), iterator_y);
      letter_matrix.light(test(iterator + iterator_y + 3), iterator_y);
      letter_matrix.light(test(iterator + iterator_y + 4), iterator_y);
      letter_matrix.light(test(iterator + iterator_y + 5), iterator_y);
    }
    board.update(letter_matrix.matrix);
    iterator = (iterator + 1) % (CLOCK_W * 2 - 1 );
  }
}

int Master::test(int i){
  int value = 0;
  if(i >= ((CLOCK_W-1) * 2)){
    i = i % ((CLOCK_W-1) * 2);
  }
  value = i;
  if(i >= CLOCK_W){
    value = 2*(CLOCK_W-1) - i;
  }
  return value;
}
