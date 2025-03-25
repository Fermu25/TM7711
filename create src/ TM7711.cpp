#include "TM7711.h"

TM7711::TM7711(uint8_t doutPin, uint8_t clkPin, Mode mode, bool powered)
    : _doutPin(doutPin), _clkPin(clkPin), _mode(mode) {
  pinMode(_doutPin, INPUT);
  pinMode(_clkPin, OUTPUT);
  digitalWrite(_clkPin, LOW);
  if (powered) {
    powerUp();
  }
}

uint32_t TM7711::readValue() {
  uint32_t value = 0;

  while (digitalRead(_doutPin)); // Esperar a que DOUT esté en bajo

  for (int i = 0; i < numBits; ++i) {
    value <<= 1;
    digitalWrite(_clkPin, HIGH);
    delayMicroseconds(1);
    if (digitalRead(_doutPin)) {
      value |= 1;
    }
    digitalWrite(_clkPin, LOW);
    delayMicroseconds(1);
  }

  // Pulsos adicionales según modo
  int pulses = 0;
  switch (_mode) {
    case Differential_10Hz:     pulses = 1; break;
    case Temperature_40Hz:      pulses = 2; break;
    case Differential_40Hz:     pulses = 3; break;
  }

  for (int i = 0; i < pulses; ++i) {
    digitalWrite(_clkPin, HIGH);
    delayMicroseconds(1);
    digitalWrite(_clkPin, LOW);
    delayMicroseconds(1);
  }

  return value;
}

void TM7711::setMode(Mode mode) {
  if (_mode == mode) return;
  _mode = mode;
  readValue(); // Establece el modo con pulsos adicionales
  initDelay();
}

void TM7711::powerDown() {
  digitalWrite(_clkPin, HIGH);
}

void TM7711::powerUp() {
  digitalWrite(_clkPin, LOW);
  initDelay();
}

void TM7711::initDelay() {
  for (int i = 0; i < 4; ++i) {
    digitalWrite(_clkPin, HIGH);
    delayMicroseconds(1);
    digitalWrite(_clkPin, LOW);
    delayMicroseconds(1);
  }
}
