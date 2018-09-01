#include <Arduino.h>

#include "hmi/Keyboard.h"
#include "server/MIDIServer.h"

MIDIServer server;
Keyboard keyboard;

void setup() {
  Serial.begin(115200);
  Serial.println();
  Serial.println("*******************************************************");
  Serial.println("*  Lightroom Mate                                     *");
  Serial.println("*  Copyright(C) 2018 MagicCube. All rights reserved.  *");
  Serial.println("*******************************************************\n");

  keyboard.registerKey(23, 1);
  keyboard.onKeyDown([](KeyEventArgs e) { Serial.print("Key down"); });
  keyboard.onKeyUp([](KeyEventArgs e) { Serial.println("Key up"); });
  keyboard.begin();

  server.begin();
}

void loop() {
  keyboard.update();
}
