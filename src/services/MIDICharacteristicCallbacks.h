#pragma once

#include <BLEUtils.h>

class MIDIService;

class MIDICharacteristicCallbacks : public BLECharacteristicCallbacks {
public:
  MIDICharacteristicCallbacks(MIDIService *midiService);

  void onWrite(BLECharacteristic *characteristic);

private:
  MIDIService *_midiService;
};
