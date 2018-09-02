#include "Encoder.h"

#include <cmath>

#include "../collections/List.h"

#define ENCODER_MAX_VALUE 127
#define ENCODER_INITIAL_VALUE 63
#define ENCODER_MIN_VALUE 0

static List<AiEsp32RotaryEncoder *> _encoders;

Encoder::Encoder(uint8_t index, uint8_t clkPin, uint8_t dtPin) : _encoder(clkPin, dtPin, -1, -1) {
  _index = index;
  _encoders.add(&_encoder);
}

uint8_t Encoder::getIndex() {
  return _index;
}

uint8_t Encoder::getValue() {
  return _value;
}

void Encoder::setValue(uint8_t value) {
  _value = value;
  _encoder.reset(ENCODER_MAX_VALUE - _value);
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
    auto newValue = ENCODER_MAX_VALUE - _encoder.readEncoder();
    if (_value != newValue) {
      _value = newValue;
      if (_onChange) {
        _onChange(EncoderEventArgs(_index, _value));
      }
    }
  }
}

void Encoder::reset() {
  setValue(ENCODER_INITIAL_VALUE);
}
