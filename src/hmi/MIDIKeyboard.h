#pragma once

#include <Arduino.h>

#include "MIDIKey.h"

#include "../collections/List.h"

class MIDIKeyboard {
public:
  MIDIKeyboard();

  void begin();
  void update();
  void registerKey(uint8_t pin, MIDINote note);

private:
  void _handleKeyDown(MIDIKeyEventArgs e);
  void _handleKeyUp(MIDIKeyEventArgs e);

  List<MIDIKey *> _keys;
  MIDIKeyEventHandler _keyDownEventHandler = NULL;
  MIDIKeyEventHandler _keyUpEventHandler = NULL;
};
