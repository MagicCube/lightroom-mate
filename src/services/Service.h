#pragma once

#include <Arduino.h>

#include <BLEUtils.h>

class LRMServer;

class Service {
public:
  Service(LRMServer *server, String serviceUUID);

  virtual void begin();
  BLECharacteristic *createCharacteristic(String uuid, uint32_t properties);

private:
  LRMServer *_server;
  BLEService *_bleService;
};
