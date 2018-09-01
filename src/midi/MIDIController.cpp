#include "MIDIController.h"

MIDIController::MIDIController(MIDIProvider *midiProvider) {
  _midiProvider = midiProvider;
}

void MIDIController::registerKey(uint8_t pin, uint8_t note) {
  Key *key = new Key(pin, note);
  key->onKeyDown(std::bind(&MIDIController::_handleKeyDown, this, placeholders::_1));
  key->onKeyUp(std::bind(&MIDIController::_handleKeyUp, this, placeholders::_1));
  _keys.add(key);
}

void MIDIController::begin() {
  for (auto key : _keys) {
    key->begin();
  }
}

void MIDIController::update() {
  for (auto key : _keys) {
    key->update();
  }
}

void MIDIController::_handleKeyDown(KeyEventArgs e) {
  _midiProvider->sendMIDIEvent(0x90, 60, 127);
}

void MIDIController::_handleKeyUp(KeyEventArgs e) {
  _midiProvider->sendMIDIEvent(0x80, 60, 0);
}
