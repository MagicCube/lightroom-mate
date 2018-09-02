#include "MIDICharacteristicCallbacks.h"

#include "MIDIService.h"

MIDICharacteristicCallbacks::MIDICharacteristicCallbacks(MIDIService *midiService) {
  _midiService = midiService;
}

void MIDICharacteristicCallbacks::onWrite(BLECharacteristic *characteristic) {
  Serial.println("[CLIENT]\tonWrite");
  std::string value = characteristic->getValue().c_str();
  if (value.length() == 5) {
    MIDIEventArgs event = MIDIEventArgs::parse(value.c_str());
    _midiService->receiveMIDIEvent(event);
  }
}
