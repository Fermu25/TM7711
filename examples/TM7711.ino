#include <TM7711.h>

TM7711 adc(4, 5); // DOUT pin = 4, CLK pin = 5

void setup() {
  Serial.begin(9600);
  adc.setMode(TM7711::Differential_10Hz);
}

void loop() {
  uint32_t value = adc.readValue();
  Serial.println(value);
  delay(500);
}
