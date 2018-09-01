#pragma once

#include <Arduino.h>

#include <functional>

#include "../midi/MIDINote.h"

enum class KeyState { UP = HIGH, DOWN = LOW };

struct MIDIKeyEventArgs {
  MIDIKeyEventArgs(MIDINote p_note) {
    note = p_note;
  }

  MIDINote note;
};

typedef std::function<void(MIDIKeyEventArgs)> MIDIKeyEventHandler;

class MIDIKey {
public:
  MIDIKey(uint8_t pin, MIDINote note);

  void onKeyDown(MIDIKeyEventHandler handler);
  void onKeyUp(MIDIKeyEventHandler handler);

  void begin();
  void update();

private:
  void _setState(KeyState state);

  uint8_t _pin;
  MIDINote _note;
  KeyState _state = KeyState::UP;
  unsigned long _lastStateChange = 0;

  MIDIKeyEventHandler _onKeyDown = NULL;
  MIDIKeyEventHandler _onKeyUp = NULL;
};
