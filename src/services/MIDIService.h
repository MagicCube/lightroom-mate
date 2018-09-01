#pragma once

#include <Arduino.h>

#include <BLE2902.h>
#include <BLEDevice.h>
#include <BLEServer.h>
#include <BLEUtils.h>

#include "../constants.h"

class LRMServer;

// Represents a Apple BLE MIDI service.
class MIDIService {
public:
  MIDIService(LRMServer *server);

  void begin();

private:
  LRMServer *_lrmServer;
  BLEService *_bleService;
  BLECharacteristic *_bleCharacteristic;
};
