#pragma once

#include <Arduino.h>

#include "../constants.h"

#include "../collections/List.h"
#include "../hmi/Encoder.h"
#include "../hmi/Key.h"

#include "MIDIProvider.h"

class MIDIController {
public:
  MIDIController(MIDIProvider *midiProvider);

  uint8_t getChannel();
  void setChannel(uint8_t channel);

  Key *registerKey(uint8_t pin);
  Encoder *registerEncoder(uint8_t clkPin, uint8_t dtPin, uint8_t swPin);

  void begin();
  void update();

private:
  MIDIProvider *_midiProvider;

  uint8_t _channel = 1;
  List<Key *> _keys;
  List<Encoder *> _encoders;

  uint8_t _midiControllerIndex = MIDI_CONTINUOUS_CONTROLLER_08;
  uint8_t _midiNoteIndex = MIDI_NOTE_C4;

  void _handleKeyDown(KeyEventArgs e);
  void _handleKeyUp(KeyEventArgs e);
  void _handleEncoderChange(EncoderEventArgs e);
};
