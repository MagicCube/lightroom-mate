#pragma once

#include <Arduino.h>

#include <BLE2902.h>
#include <BLEDevice.h>
#include <BLEServer.h>
#include <BLEUtils.h>

#include "../constants.h"

// Represents a Apple BLE MIDI service.
class MIDIService {
public:
  MIDIService(BLEServer *bleServer);

  void begin();

private:
  BLEServer *_bleServer;
  BLEService *_bleService;
  BLECharacteristic *_bleCharacteristic;
};
