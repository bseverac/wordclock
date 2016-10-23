#include "app/master.h"
#include <stdio.h>
#include <util/delay.h>
#include <avr/io.h>
#include <avr/interrupt.h>

#include "hardware/handle_uart.h"
#include "hardware/lib-ino/twi.h"
#include "hardware/lib-ino/rtc.h"
#include "hardware/lib-ino/uart.h"

Master master;
HandleUart handle_uart;
/*ISR(TIMER1_OVF_vect) {
  TCNT1=0x0BDC;
  master.update_time(1000);
}*/

/*void init_timer0(){
  TCCR1A = 0;
  TCCR1B = 0;
  TIMSK1 |= (1 << TOIE1);
  TCNT1 = 0x0BDC;
  TCCR1B |= (1 << CS12); // Sets bit CS12 in TCCR1B
  sei();
}*/

int main()
{
  struct tm* t = NULL;
  handle_uart.init();

  //init_timer0();
  while(true) {
    t = rtc_get_time();
    master.set_time(t->hour, t->min, t->sec);
    master.loop(handle_uart.mode, handle_uart.value);
    handle_uart.handle();
    _delay_ms(1000/30);
  }
}
