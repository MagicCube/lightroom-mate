#pragma once

#include <Arduino.h>

#include "Service.h"

#include "../constants.h"

class LRMServer;

// Represents a Apple BLE MIDI service.
class MIDIService : public Service {
public:
  MIDIService(LRMServer *server);

  void begin();

private:
  BLECharacteristic *_bleCharacteristic;
};
