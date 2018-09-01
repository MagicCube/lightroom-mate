#pragma once

#include <Arduino.h>

#include <AiEsp32RotaryEncoder.h>

#include "EncoderEvent.h"

class Encoder {
public:
  Encoder(uint8_t code, uint8_t clkPin, uint8_t dtPin);

  void onChange(EncoderEventHandler handler);

  void begin();
  void update();

private:
  AiEsp32RotaryEncoder _encoder;
  uint8_t _code;
  uint16_t _value = 64;
  EncoderEventHandler _onChange = NULL;
  unsigned long _lastUpdate = 0;
};
