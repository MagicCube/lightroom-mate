#include "MIDIKey.h"

MIDIKey::MIDIKey(uint8_t pin, uint8_t note) {
  _pin = pin;
  _note = note;
}

void MIDIKey::onKeyDown(KeyEventHandler handler) {
  _onKeyDown = handler;
}

void MIDIKey::onKeyUp(KeyEventHandler handler) {
  _onKeyUp = handler;
}

void MIDIKey::begin() {
  pinMode(_pin, INPUT_PULLUP);
}

void MIDIKey::update() {
  KeyState value = (KeyState)digitalRead(_pin);
  auto sinceLastChange = millis() - _lastStateChange;
  if (value == _state || sinceLastChange < 120) {
    return;
  }
  if (value == KeyState::DOWN) {
    _setState(KeyState::DOWN);
  } else if (value == KeyState::UP) {
    _setState(KeyState::UP);
  }
}

void MIDIKey::_setState(KeyState value) {
  _state = value;
  _lastStateChange = millis();
  if (_state == KeyState::DOWN) {
    if (_onKeyDown) {
      _onKeyDown(MIDIKeyEventArgs(_note));
    }
  } else {
    if (_onKeyUp) {
      _onKeyUp(MIDIKeyEventArgs(_note));
    }
  }
}
