#include "MIDIController.h"

MIDIController::MIDIController(MIDIProvider *midiProvider) {
  _midiProvider = midiProvider;
}

void MIDIController::registerKey(uint8_t note, uint8_t pin) {
  Key *key = new Key(note, pin);
  key->onKeyDown(std::bind(&MIDIController::_handleKeyDown, this, placeholders::_1));
  key->onKeyUp(std::bind(&MIDIController::_handleKeyUp, this, placeholders::_1));
  _keys.add(key);
}

void MIDIController::registerEncoder(uint8_t controllerId, uint8_t clkPin, uint8_t dtPin) {
  Encoder *encoder = new Encoder(controllerId, clkPin, dtPin);
  encoder->onChange(std::bind(&MIDIController::_handleEncoderChange, this, placeholders::_1));
  _encoders.add(encoder);
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
  _midiProvider->sendMIDIEvent(0x90, e.code, 127);
}

void MIDIController::_handleKeyUp(KeyEventArgs e) {
  _midiProvider->sendMIDIEvent(0x80, e.code, 0);
}

void MIDIController::_handleEncoderChange(EncoderEventArgs e) {
  _midiProvider->sendMIDIEvent(0xb0, e.code, e.value);
}
