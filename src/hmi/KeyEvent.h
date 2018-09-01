#pragma once

#include <Arduino.h>

#include <functional>

struct KeyEventArgs {
  KeyEventArgs(uint8_t p_code) {
    code = p_code;
  }

  uint8_t code;
};

typedef std::function<void(KeyEventArgs)> KeyEventHandler;
