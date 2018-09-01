#pragma once

#include <Arduino.h>

#include "Key.h"

#include "../collections/List.h"

class Keyboard {
public:
  Keyboard();

  void begin();
  void update();
  void registerKey(uint8_t pin, uint8_t note);

private:
  void _handleKeyDown(KeyEventArgs e);
  void _handleKeyUp(KeyEventArgs e);

  List<Key *> _keys;
  KeyEventHandler _keyDownEventHandler = NULL;
  KeyEventHandler _keyUpEventHandler = NULL;
};
