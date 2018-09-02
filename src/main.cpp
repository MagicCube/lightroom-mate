#include <Arduino.h>

#include <SH1106Wire.h>

#include "constants.h"
#include "midi/MIDIController.h"
#include "server/LRMServer.h"

String deviceName;
LRMServer *server;
MIDIController *controller;

// SDA, SCL
SH1106Wire display(0x3c, 21, 22);

void initBLE() {
  auto chipId = ESP.getEfuseMac();
  auto shortId = String((uint32_t)chipId);
  // Only use the last 4 byte as ID
  deviceName = "LR" + shortId.substring(shortId.length() - 3);
  BLEDevice::init(deviceName.c_str());
  BLEDevice::setEncryptionLevel((esp_ble_sec_act_t)ESP_LE_AUTH_REQ_SC_BOND);
  Serial.print("BLE device [");
  Serial.print(deviceName);
  Serial.print("] is now initialized.");
  Serial.println();
}

void initDisplay() {
  display.init();
  display.flipScreenVertically();
  display.clear();
  display.drawString(0, 0, "Hello");
  display.display();
}

void initServer() {
  server = new LRMServer();
  server->begin();
}

void initController() {
  controller = new MIDIController(server->getMIDIService());
  controller->registerEncoder(4, 16, 17);
  controller->registerEncoder(5, 18, 19);
  controller->registerEncoder(15, 34, 23);

  controller->registerEncoder(26, 27, 14);
  controller->registerEncoder(25, 33, 32);

  controller->begin();
}

void setup() {
  Serial.begin(115200);
  Serial.println();
  Serial.println();
  Serial.println("*******************************************************");
  Serial.println("*  Lightroom Mate                                     *");
  Serial.println("*  Copyright(C) 2018 Henry Li. All rights reserved.   *");
  Serial.println("*******************************************************\n");

  initDisplay();
  initBLE();
  initServer();
  initController();
}

void loop() {
  controller->update();
}
