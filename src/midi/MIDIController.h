#pragma once

#include <Arduino.h>

#include "../collections/List.h"
#include "../hmi/Encoder.h"
#include "../hmi/Key.h"

#include "MIDIProvider.h"

class MIDIController {
public:
  MIDIController(MIDIProvider *midiProvider);

  uint8_t getChannel();
  void setChannel(uint8_t channel);

  void registerKey(uint8_t note, uint8_t pin);
  void registerEncoder(uint8_t controllerId, uint8_t clkPin, uint8_t dtPin);

  void begin();
  void update();

private:
  MIDIProvider *_midiProvider;

  uint8_t _channel = 1;
  List<Key *> _keys;
  List<Encoder *> _encoders;

  void _handleKeyDown(KeyEventArgs e);
  void _handleKeyUp(KeyEventArgs e);
  void _handleEncoderChange(EncoderEventArgs e);
};
