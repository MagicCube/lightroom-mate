#pragma once

#include <Arduino.h>

#include <functional>

struct EncoderEventArgs {
  EncoderEventArgs(uint8_t p_index, uint8_t p_value) {
    index = p_index;
    value = p_value;
  }

  uint8_t index;
  uint8_t value;
};

typedef std::function<void(EncoderEventArgs)> EncoderEventHandler;
