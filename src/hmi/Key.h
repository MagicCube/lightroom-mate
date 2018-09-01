#pragma once

#include <Arduino.h>

#include <functional>

#include "Encoder.h"
#include "KeyEvent.h"
#include "KeyState.h"

class Key {
public:
  Key(uint8_t code, uint8_t pin);

  Encoder *getEncoder();
  void setEncoder(Encoder *encoder);

  void onKeyDown(KeyEventHandler handler);
  void onKeyUp(KeyEventHandler handler);

  void begin();
  void update();

private:
  void _setState(KeyState state);

  Encoder *_encoder;

  uint8_t _pin;
  uint8_t _code;
  KeyState _state = KeyState::UP;
  unsigned long _lastStateChange = 0;

  KeyEventHandler _onKeyDown = NULL;
  KeyEventHandler _onKeyUp = NULL;
};
