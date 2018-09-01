#pragma once

#include <Arduino.h>

#include "../collections/List.h"
#include "../hmi/Key.h"
#include "../services/MIDIService.h"

class MIDIController {
public:
  MIDIController(MIDIService *midiService);

  void registerKey(uint8_t pin, uint8_t note);

  void begin();
  void update();

private:
  MIDIService *_midiService;

  List<Key *> _keys;

  void _handleKeyDown(KeyEventArgs e);
  void _handleKeyUp(KeyEventArgs e);
};
