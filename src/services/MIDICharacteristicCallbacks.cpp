#include "MIDICharacteristicCallbacks.h"

#include "MIDIService.h"

MIDICharacteristicCallbacks::MIDICharacteristicCallbacks(MIDIService *midiService) {
  _midiService = midiService;
}

void MIDICharacteristicCallbacks::onWrite(BLECharacteristic *characteristic) {
  std::string value = characteristic->getValue().c_str();
  if (value.length() == 5) {
    MIDIEvent event = MIDIEvent::parse(value.c_str());
    _midiService->receiveMIDIEvent(event);
  }
}
