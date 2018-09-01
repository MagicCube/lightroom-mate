#include "Key.h"

Key::Key(uint8_t pin, uint8_t code) {
  _pin = pin;
  _code = code;
}

void Key::onKeyDown(KeyEventHandler handler) {
  _onKeyDown = handler;
}

void Key::onKeyUp(KeyEventHandler handler) {
  _onKeyUp = handler;
}

void Key::begin() {
  pinMode(_pin, INPUT_PULLUP);
}

void Key::update() {
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

void Key::_setState(KeyState value) {
  _state = value;
  _lastStateChange = millis();
  if (_state == KeyState::DOWN) {
    if (_onKeyDown) {
      _onKeyDown(KeyEventArgs(_code));
    }
  } else {
    if (_onKeyUp) {
      _onKeyUp(KeyEventArgs(_code));
    }
  }
}