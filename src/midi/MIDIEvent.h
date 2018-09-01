#pragma once

#include <Arduino.h>

enum class MIDIEventType : uint8_t {
  NOTE_OFF = 0x80,
  NOTE_ON = 0x90,
  CONTROL_MODE_CHANGE = 0xb0,
};

struct MIDIEvent {
  MIDIEvent(MIDIEventType p_type, uint8_t p_channel, uint8_t p_index, uint8_t p_value) {
    type = p_type;
    channel = p_channel;
    index = p_index;
    value = p_value;
  }

  void toArray(uint8_t *arr) {
    arr[0] = 0x80;                          // 0 - header
    arr[1] = 0x80;                          // 1 - timestamp, not implemented
    arr[2] = (uint8_t)type + (channel - 1); // 2 - type
    arr[3] = index;                         // 3 - index
    arr[4] = value;                         // 4 - value
  }

  MIDIEventType type;
  uint8_t channel;
  uint8_t index;
  uint8_t value;
};
