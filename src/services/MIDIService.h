#pragma once

#include <Arduino.h>

#include "Service.h"

#include "../constants.h"

#include "../midi/MIDIProvider.h"

class LRMServer;

// Represents a Apple BLE MIDI service.
class MIDIService : public Service, public MIDIProvider {
public:
  MIDIService(LRMServer *server);

  void begin();

  void sendMIDIEvent(uint8_t type, uint8_t id, uint8_t value);

private:
  BLECharacteristic *_bleCharacteristic;
};
