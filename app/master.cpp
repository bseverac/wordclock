#include "master.h"

Master::Master(){
}

void Master::loop(int elapse){
  clock.loop(elapse);
  board.update(clock.led_status);
}
