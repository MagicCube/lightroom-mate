#include "Key.h"

Key::Key(uint8_t code, uint8_t pin) {
  _code = code;
  _pin = pin;
}

uint8_t Key::getIndex() {
  return _code;
}

Encoder *Key::getEncoder() {
  return _encoder;
}
void Key::setEncoder(Encoder *encoder) {
  _encoder = encoder;
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
      _onKeyDown(KeyEventArgs(this, _code));
    }
  } else {
    if (_onKeyUp) {
      _onKeyUp(KeyEventArgs(this, _code));
    }
  }
}
