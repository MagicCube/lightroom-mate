#include "MIDIService.h"

#include "../server/LRMServer.h"

MIDIService::MIDIService(LRMServer *server) {
  _lrmServer = server;
  _bleService = _lrmServer->createBLEService(MIDI_SERVICE_UUID);
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
