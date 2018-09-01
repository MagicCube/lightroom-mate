#include "MIDIService.h"

MIDIService::MIDIService(BLEServer *server) {
  _bleServer = server;
  _bleService = _bleServer->createService(BLEUUID(MIDI_SERVICE_UUID));
  _bleCharacteristic = _bleService->createCharacteristic(BLEUUID(MIDI_CHARACTERISTIC_UUID),
                                                         BLECharacteristic::PROPERTY_READ |
                                                             BLECharacteristic::PROPERTY_NOTIFY |
                                                             BLECharacteristic::PROPERTY_WRITE_NR);
  _bleCharacteristic->addDescriptor(new BLE2902());
}

void MIDIService::begin() {
  _bleService->start();
  Serial.println("MIDI service is now started.");
}
