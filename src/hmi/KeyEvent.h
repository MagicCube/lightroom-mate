#pragma once

#include <Arduino.h>

#include <functional>

class Key;

struct KeyEventArgs {
  KeyEventArgs(Key *p_target, uint8_t p_index) {
    target = p_target;
    index = p_index;
  }

  Key *target;
  uint8_t index;
};

typedef std::function<void(KeyEventArgs)> KeyEventHandler;
