#include "Keyboard.h"

Keyboard::Keyboard() {
  _keyDownEventHandler = [this](KeyEventArgs e) { _handleKeyDown(e); };
  _keyUpEventHandler = [this](KeyEventArgs e) { _handleKeyUp(e); };
}

void Keyboard::begin() {
  for (auto key : _keys) {
    key->begin();
  }
}

void Keyboard::update() {
  for (auto key : _keys) {
    key->update();
  }
}

void Keyboard::registerKey(uint8_t pin, uint8_t note) {
  Key *key = new Key(pin, note);
  key->onKeyDown(_keyDownEventHandler);
  key->onKeyUp(_keyUpEventHandler);
  _keys.add(key);
}

void Keyboard::_handleKeyDown(KeyEventArgs e) {
  Serial.print("Key down");
}

void Keyboard::_handleKeyUp(KeyEventArgs e) {
  Serial.println(" - up");
}
