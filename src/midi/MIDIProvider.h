#pragma once

#include <Arduino.h>

#include "MIDIEvent.h"

class MIDIProvider {
public:
  virtual void sendMIDIEvent(MIDIEventArgs event);
  virtual void sendMIDIEvent(MIDIEventType type, uint8_t channel, uint8_t index, uint8_t value) {
    MIDIEventArgs event(type, channel, index, value);
    sendMIDIEvent(event);
  }
};
