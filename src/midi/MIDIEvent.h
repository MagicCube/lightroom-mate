#pragma once

#include <Arduino.h>

enum class MIDIEventType : uint8_t {
  UNKNOWN = 0x00,
  NOTE_OFF = 0x80,
  NOTE_ON = 0x90,
  CONTROL_CHANGE = 0xb0,
  CONTROL_ON_CHANGE = 0x01
};

struct MIDIEvent {
  MIDIEvent(MIDIEventType p_type) {
    type = p_type;
  }

  MIDIEvent(MIDIEventType p_type, uint8_t p_channel, uint8_t p_index, uint8_t p_value) {
    type = p_type;
    channel = p_channel;
    index = p_index;
    value = p_value;
  }

  static MIDIEvent parse(const char *chars) {
    MIDIEvent event(MIDIEventType::UNKNOWN);
    uint8_t v = chars[2];
    if (v >= (uint8_t)MIDIEventType::CONTROL_CHANGE &&
        v <= (uint8_t)MIDIEventType::CONTROL_CHANGE + 16) {
      event.type = MIDIEventType::CONTROL_ON_CHANGE;
      event.channel = (uint8_t)chars[2] - (uint8_t)MIDIEventType::CONTROL_CHANGE + 1;
      event.index = (uint8_t)chars[3];
      event.value = (uint8_t)chars[4];
    }
    return event;
  }

  void toArray(uint8_t *arr) {
    arr[0] = 0x80;                        // 0 - header
    arr[1] = 0x80;                        // 1 - timestamp, not implemented
    arr[2] = (uint8_t)type + channel - 1; // 2 - type
    arr[3] = index;                       // 3 - index
    arr[4] = value;                       // 4 - value
  }

  MIDIEventType type;
  uint8_t channel;
  uint8_t index;
  uint8_t value;
};
