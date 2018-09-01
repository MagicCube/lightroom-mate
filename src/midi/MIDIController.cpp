#include "MIDIController.h"

#include "../midi/MIDIEvent.h"

MIDIController::MIDIController(MIDIProvider *midiProvider) {
  _midiProvider = midiProvider;
}

uint8_t MIDIController::getChannel() {
  return _channel;
}

void MIDIController::setChannel(uint8_t channel) {
  _channel = channel;
}

Key *MIDIController::registerKey(uint8_t note, uint8_t pin) {
  Key *key = new Key(note, pin);
  key->onKeyDown(std::bind(&MIDIController::_handleKeyDown, this, placeholders::_1));
  key->onKeyUp(std::bind(&MIDIController::_handleKeyUp, this, placeholders::_1));
  _keys.add(key);
  return key;
}

Encoder *MIDIController::registerEncoder(uint8_t controllerId, uint8_t note, uint8_t clkPin,
                                         uint8_t dtPin, uint8_t swPin) {
  Encoder *encoder = new Encoder(controllerId, clkPin, dtPin);
  encoder->onChange(std::bind(&MIDIController::_handleEncoderChange, this, placeholders::_1));
  _encoders.add(encoder);
  auto key = registerKey(note, swPin);
  key->setEncoder(encoder);
  return encoder;
}

void MIDIController::begin() {
  for (auto key : _keys) {
    key->begin();
  }
  for (auto encoder : _encoders) {
    encoder->begin();
  }
}

void MIDIController::update() {
  for (auto key : _keys) {
    key->update();
  }
  for (auto encoder : _encoders) {
    encoder->update();
  }
}

void MIDIController::_handleKeyDown(KeyEventArgs e) {
  _midiProvider->sendMIDIEvent(MIDIEventType::NOTE_ON, getChannel(), e.code, 127);
  auto encoder = e.target->getEncoder();
  if (encoder) {
    encoder->reset();
  }
}

void MIDIController::_handleKeyUp(KeyEventArgs e) {
  _midiProvider->sendMIDIEvent(MIDIEventType::NOTE_OFF, getChannel(), e.code, 0);
}

void MIDIController::_handleEncoderChange(EncoderEventArgs e) {
  _midiProvider->sendMIDIEvent(MIDIEventType::CONTROL_MODE_CHANGE, getChannel(), e.code, e.value);
}
