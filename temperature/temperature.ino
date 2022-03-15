#include "segment.h"

// Some const for the temperature
const int B = 4275;               // B value of the thermistor
const int R0 = 100000;            // R0 = 100k
const int pinTempSensor = A0;     // Grove - Temperature Sensor connect to A0


void setup() {
  init_display();
  enable_output(true);
  delay(1000);
}

void loop() {
  // Put your own code for the temperature
  int a = analogRead(pinTempSensor);
  float R = 1023.0/a-1.0;
  R = R0*R;
  float temperature = 1.0/(log(R/R0)/B+1/298.15)-273.15;

  
  set_digit(0, (int)temperature/10);
  set_digit(1, (int)temperature%10);
  set_digit(2, (int)(temperature*10)%10);
  set_digit(3, (int)(temperature*100)%10);
  refresh_display();
  delay(500);
}
