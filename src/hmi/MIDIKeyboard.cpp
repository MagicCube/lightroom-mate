#include "MIDIKeyboard.h"

#include "MIDIKey.h"

MIDIKeyboard::MIDIKeyboard() {
  _keyDownEventHandler = [this](MIDIKeyEventArgs e) { _handleKeyDown(e); };
  _keyUpEventHandler = [this](MIDIKeyEventArgs e) { _handleKeyUp(e); };
}

void MIDIKeyboard::begin() {
  for (auto key : _keys) {
    key->begin();
  }
}

void MIDIKeyboard::update() {
  for (auto key : _keys) {
    key->update();
  }
}

void MIDIKeyboard::registerKey(uint8_t pin, MIDINote note) {
  MIDIKey *key = new MIDIKey(pin, note);
  key->onKeyDown(_keyDownEventHandler);
  key->onKeyUp(_keyUpEventHandler);
  _keys.add(key);
}

void MIDIKeyboard::_handleKeyDown(MIDIKeyEventArgs e) {
  Serial.print("Key down");
}

void MIDIKeyboard::_handleKeyUp(MIDIKeyEventArgs e) {
  Serial.println(" - up");
}
