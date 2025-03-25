#pragma once

#include <Arduino.h>

class TM7711 {
public:
  enum Mode {
    Differential_10Hz,
    Temperature_40Hz,
    Differential_40Hz
  };

  TM7711(uint8_t doutPin, uint8_t clkPin, Mode mode = Differential_10Hz, bool powered = true);

  uint32_t readValue();
  void setMode(Mode mode);
  void powerDown();
  void powerUp();

private:
  void initDelay();

  uint8_t _doutPin;
  uint8_t _clkPin;
  Mode _mode;

  static const int numBits = 24;
};
