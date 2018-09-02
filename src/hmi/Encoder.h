#pragma once

#include <Arduino.h>

#include <AiEsp32RotaryEncoder.h>

#include "EncoderEvent.h"

class Encoder {
public:
  Encoder(uint8_t index, uint8_t clkPin, uint8_t dtPin);

  uint8_t getIndex();

  uint8_t getValue();
  void setValue(uint8_t value);

  void onChange(EncoderEventHandler handler);

  void begin();
  void update();
  void reset();

private:
  AiEsp32RotaryEncoder _encoder;
  uint8_t _index;
  uint8_t _value = 64;
  EncoderEventHandler _onChange = NULL;
  unsigned long _lastUpdate = 0;
};
