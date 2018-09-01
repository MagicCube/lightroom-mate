#pragma once

#include <Arduino.h>

#include "../collections/List.h"
#include "../hmi/Key.h"

#include "MIDIProvider.h"

class MIDIController {
public:
  MIDIController(MIDIProvider *midiProvider);

  void registerKey(uint8_t pin, uint8_t note);

  void begin();
  void update();

private:
  MIDIProvider *_midiProvider;

  List<Key *> _keys;

  void _handleKeyDown(KeyEventArgs e);
  void _handleKeyUp(KeyEventArgs e);
};
