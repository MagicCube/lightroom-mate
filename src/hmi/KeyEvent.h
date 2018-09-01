#pragma once

#include <Arduino.h>

#include <functional>

class Key;

struct KeyEventArgs {
  KeyEventArgs(Key *p_target, uint8_t p_code) {
    target = p_target;
    code = p_code;
  }

  Key *target;
  uint8_t code;
};

typedef std::function<void(KeyEventArgs)> KeyEventHandler;
