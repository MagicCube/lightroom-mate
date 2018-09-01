#pragma once

#include <Arduino.h>

#include <functional>

struct EncoderEventArgs {
  EncoderEventArgs(uint8_t p_code, uint8_t p_value) {
    code = p_code;
    value = p_value;
  }

  uint8_t code;
  uint8_t value;
};

typedef std::function<void(EncoderEventArgs)> EncoderEventHandler;
