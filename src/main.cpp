#include <Arduino.h>

#include "constants.h"
#include "midi/MIDIController.h"
#include "server/LRMServer.h"

LRMServer *server;
MIDIController *controller;

void initBLE() {
  auto chipId = ESP.getEfuseMac();
  // Only use the last 4 byte as ID
  String name = String("LightroomMate-" + String((uint32_t)chipId));
  BLEDevice::init(name.c_str());
}

void initServer() {
  server = new LRMServer();
  server->begin();
}

void initController() {
  controller = new MIDIController(server->getMIDIService());
  controller->registerEncoder(MIDI_CONTINUOUS_CONTROLLER_08, MIDI_NOTE_C4, 21, 22, 23);
  controller->begin();
}

void setup() {
  Serial.begin(115200);
  Serial.println();
  Serial.println("*******************************************************");
  Serial.println("*  Lightroom Mate                                     *");
  Serial.println("*  Copyright(C) 2018 Henry Li. All rights reserved.   *");
  Serial.println("*******************************************************\n");

  initBLE();
  initServer();
  initController();
}

void loop() {
  controller->update();
}
