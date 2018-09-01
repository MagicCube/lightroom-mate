#include <Arduino.h>

#include "midi/MIDIController.h"
#include "server/LRMServer.h"

LRMServer *server;
MIDIController *controller;

void setup() {
  Serial.begin(115200);
  Serial.println();
  Serial.println("*******************************************************");
  Serial.println("*  Lightroom Mate                                     *");
  Serial.println("*  Copyright(C) 2018 MagicCube. All rights reserved.  *");
  Serial.println("*******************************************************\n");

  auto chipId = ESP.getEfuseMac();
  // Only use the last 4 byte as ID
  String name = String("LightroomMate-" + String((uint32_t)chipId));
  BLEDevice::init(name.c_str());

  server = new LRMServer();
  // Start server
  server->begin();

  // Setup controller
  controller = new MIDIController(server->getMIDIService());
  controller->registerKey(60, 23);
  controller->begin();
}

void loop() {
  controller->update();
}
