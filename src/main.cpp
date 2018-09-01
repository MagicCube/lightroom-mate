#include <Arduino.h>

#include "server/MIDIServer.h"

MIDIServer server;

void setup() {
  Serial.begin(115200);
  Serial.println();
  Serial.println("*******************************************************");
  Serial.println("*  Lightroom Mate                                     *");
  Serial.println("*  Copyright(C) 2018 MagicCube. All rights reserved.  *");
  Serial.println("*******************************************************\n");

  server.begin();
}

void loop() {
}
