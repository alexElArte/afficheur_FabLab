#include "segment.h"

void setup() {
  init_display();
  enable_output(true);
}

void loop() {
  // millis() -> max ~50d
  uint32_t centi = millis() / 10;
  uint32_t seconds = centi / 100;
  uint32_t minutes = seconds / (60);
  uint32_t hours = seconds / (60*60);
  uint32_t days = seconds / (24*60*60);


  if (minutes < 1) {              // 00s 00ms - 59s 99ms
    set_digit(0, (seconds/10)%10); // AXXX
    set_digit(1, (seconds%10));    // XAXX
    set_digit(2, (centi/10)%10);   // XXAX
    set_digit(3, (centi%10));      // XXXA
  } else if (hours < 1) {        // 01min 00s - 59min 59s
    set_digit(0, (minutes/10)%10);    // AXXX
    set_digit(1, (minutes%10));    // XAXX
    set_digit(2, (seconds/10)%6);  // XXAX
    set_digit(3, (seconds%10));    // XXXA
  } else if (days < 1) {         // 01h 00min - 23h 59min
    set_digit(0, (hours/10)%10);      // AXXX
    set_digit(1, (hours%10));      // XAXX
    set_digit(2, (minutes/10)%6);  // XXAX
    set_digit(3, (minutes%10));    // XXXA
  } else {                       // 01j 00h - 99j 23h
    set_digit(0, (days/10)%10);    // AXXX
    set_digit(1, (days%10));       // XAXX
    set_digit(2, (hours/10)%6);    // XXAX
    set_digit(3, (hours%10));      // XXXA
  }
  refresh_display();

  // Some other go to write down side


}
