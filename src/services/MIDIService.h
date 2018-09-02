#pragma once

#include <Arduino.h>

#include "Service.h"

#include "../constants.h"

#include "../midi/MIDIEvent.h"
#include "../midi/MIDIProvider.h"

class LRMServer;

// Represents a Apple BLE MIDI service.
class MIDIService : public Service, public MIDIProvider {
public:
  MIDIService(LRMServer *server);

  void onReceive(MIDIEventHandler handler);

  void begin();
  void sendMIDIEvent(MIDIEventArgs event);
  void receiveMIDIEvent(MIDIEventArgs event);

private:
  BLECharacteristic *_bleCharacteristic;
  MIDIEventHandler _onReceive;
};
