#include "handle_uart.h"

HandleUart::HandleUart(){
  mode = 0;
  t = NULL;
}

void HandleUart::init(){
  uartInit();
  uartSetBaudRate(9600);
  uartSendString("hello @here");
  twi_init_master();
  rtc_init();
}

void HandleUart::handle(){
  if(!uartReceiveBufferIsEmpty()){
    b = uartGetRxBuffer();
    if(isCommand()){
      if((end - start + 1) == 23){
        handle_timeset();
        handle_info();
      }
      if((end - start + 1) == 5 && get(start) == 's'){ //set00
        handle_set();
      }
      if((end - start + 1) == 4 && get(start) == 'p'){ //ping
        handle_ping();
      }
      if((end - start + 1) == 4 && get(start) == 'i'){ //info
        handle_info();
      }
      if((end - start + 1) == 6 && get(start) == 'm'){ //mode00
        handle_mode();
      }
      uartFlushReceiveBuffer();
    }
  }
}

void HandleUart::handle_ping(){
  uartSendString("pong");

}

void HandleUart::handle_set(){
  value = get_two_digit(start + 3);
  sprintf(buf, "value: %d", value);
  uartSendString(buf);
}

void HandleUart::handle_mode(){
  mode = get_two_digit(start + 4);
  sprintf(buf, "mode: %d", mode);
  uartSendString(buf);
}
//info
void HandleUart::handle_info(){
  t = rtc_get_time();
  int8_t base;
  uint8_t floating;
  ds3231_get_temp_int(&base, &floating);
  sprintf(buf, "^%d:%d:%d-%d/%d/%d-%dT%d.%d$",
             t->hour,
             t->min,
             t->sec,
             t->mday,
             t->mon,
             t->year,
             t->wday,
             base,
             floating);
	uartSendString(buf);

}
//01234567890123456789012
//s00:00:00-31/01/2010-00
void HandleUart::handle_timeset(){
  t = rtc_get_time();
  i = start;
  t->hour = get_two_digit(i + 1);
  t->min  = get_two_digit(i + 4);
  t->sec  = get_two_digit(i + 7);
  t->mday = get_two_digit(i + 10);
  t->mon  = get_two_digit(i + 13);
  t->year = get_two_digit(i + 16) * 100 + get_two_digit(i + 18);
  t->wday = get_two_digit(i + 21);
  rtc_set_time(t);
}

int HandleUart::get_two_digit(int i){
  return (get(i) - 48) * 10 + (get(i + 1) - 48);
}

bool HandleUart::isCommand(){
  if(b->size > 2){
    start = 0;
    end = 0;
    for(i = 1; i < b->size; i++){
      if(get(i - 1) == '^'){
        start = i;
        break;
      }
    }
    for(i = start + 1; i < b->size; i++){
      if(get(i) == '$'){
        end = i - 1;
        break;
      }
    }
    return start < end;
  }else{
    return false;
  }
}

char HandleUart::get(int i){
  return bufferGetAtIndex(b, b->dataindex + i);
}
