#pragma once

#include <Arduino.h>

class MIDIProvider {
public:
  virtual void sendMIDIEvent(uint8_t type, uint8_t id, uint8_t value);
};
