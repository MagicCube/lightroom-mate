#include <Arduino.h>

#include "midi/MIDIController.h"
#include "server/LRMServer.h"

LRMServer *server = new LRMServer();
MIDIController *controller = NULL;

void setup() {
  Serial.begin(115200);
  Serial.println();
  Serial.println("*******************************************************");
  Serial.println("*  Lightroom Mate                                     *");
  Serial.println("*  Copyright(C) 2018 MagicCube. All rights reserved.  *");
  Serial.println("*******************************************************\n");

  // Start server
  server->begin();

  // Setup controller
  controller = new MIDIController(server->getMIDIService());
  controller->registerKey(23, 1);
  controller->begin();
}

void loop() {
  controller->update();
}
