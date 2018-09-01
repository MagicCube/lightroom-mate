#include "Encoder.h"

#include <cmath>

#include "../collections/List.h"

#define ENCODER_MAX_VALUE 127
#define ENCODER_INITIAL_VALUE 64
#define ENCODER_MIN_VALUE 0

static List<AiEsp32RotaryEncoder *> _encoders;

Encoder::Encoder(uint8_t code, uint8_t clkPin, uint8_t dtPin) : _encoder(clkPin, dtPin, -1, -1) {
  _code = code;
  _encoders.add(&_encoder);
}

void Encoder::onChange(EncoderEventHandler handler) {
  _onChange = handler;
}

void Encoder::begin() {
  _encoder.begin();
  _encoder.setup([]() {
    for (auto e : _encoders) {
      e->readEncoder_ISR();
    }
  });
  _encoder.setBoundaries(ENCODER_MIN_VALUE, ENCODER_MAX_VALUE, false);
  reset();
}

void Encoder::update() {
  auto delta = _encoder.encoderChanged();
  if (delta) {
    auto newValue = _encoder.readEncoder();
    if (_value != newValue) {
      _value = newValue;
      if (_onChange) {
        _onChange(EncoderEventArgs(_code, ENCODER_MAX_VALUE - _value));
      }
    }
  }
}

void Encoder::reset() {
  _value = ENCODER_INITIAL_VALUE;
  _encoder.reset(_value);
}
